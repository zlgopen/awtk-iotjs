# 集成 AWTK 到 iotjs

用 C 语言来扩展 [iotjs](http://iotjs.net/) 不是太难的事情，但是将 GUI 集成到 iotjs 却是有些麻烦的。主要原因在于 iotjs 有个主循环 (main loop)，GUI 自己也有个主循环 (main loop)，两者不同并存，只能选一个。这里 [AWTK](https://github.com/zlgopen/awtk) 为例，介绍一下如何将 GUI 集成到 iotjs 中，这对将 GUI 集成到 nodejs 也是有参考价值。

## 一、以谁为主

在集成 AWTK 到 iotjs 时，我选择了以 iotjs 的主循环为主。这并不是唯一的正确方案，做这个选择的主要原因有：

* 让 [AWTK](https://github.com/zlgopen/awtk) 作为 iotjs 的模块，保持 iotjs 本身的开发方式。

* 避免修改 iotjs。iotjs 对我来说是第三方模块，修改第三方模块，会增加后期的维护成本。

我们把 AWTK 主循环的一次循环提取成一个 step，然后把它放到 iotjs 的定时器中，每隔 16 毫秒（最大 60FPS) 调用一次，这样可以模拟 GUI 的主循环了。

```
const char* s_step_script = "\
(function() { \
  var awtkStepId = 0;\
  function awtkStep() {\
    if(!awtk_main_loop_step()) {\
      clearInterval(awtkStepId);\
      console.log(\"awtk quit\");\
      awtkStepId = 0;\
    }\
  }\
  awtkStepId = setInterval(awtkStep, 16);\
}())";

JS_FUNCTION(wrap_awtk_main_loop_step) {
  bool_t ret = FALSE;
  main_loop_t* loop = main_loop();

  if(loop != NULL) {
    main_loop_step(loop);

    ret = !(loop->app_quited);
    if(loop->app_quited) {
      tk_exit();
    }
  }

  return jerry_create_number(ret);
}
```

> 值得注意的是，这个定时器一定要放在 javascript 里去调用。
> 开始我用了 libuv 原生的定时器来实现，代码简洁而且高效，但是应用程序退出时，iotjs 就会崩掉，原因是 iotjs 认为所有的定时器都是 javascript 里的，而 javascripte 里的定时器是在原生定时器基础上包装而成，在应用程序退出时做了一些额外的释放工作。

## 二、模态对话框

模态对话框会再次调用主循环的 run，直到对话框关闭。这个时候需要在 GUI 主循环中调用 iotjs 的主循环。但是 iotjs 的循环是 libuv 主循环的基础上包装了一层，而且不适合外面再次调用，所以我仿造 iotjs 实现了一个：

```
static ret_t  main_loop_iotjs_run(main_loop_t* loop) {
  ret_t ret = RET_OK;
  iotjs_environment_t* env = iotjs_environment_get();

  if (!iotjs_environment_is_exiting(env)) {
    bool more = 0;
    do {
      more = uv_run(iotjs_environment_loop(env), UV_RUN_ONCE);
      more |= iotjs_process_next_tick();

      jerry_value_t ret_val = jerry_run_all_enqueued_jobs();
      if (jerry_value_is_error(ret_val)) {
        ret_val = jerry_get_value_from_error(ret_val, true);
        iotjs_uncaught_exception(ret_val);
        jerry_release_value(ret_val);
      }

      if (more == false) {
        more = uv_loop_alive(iotjs_environment_loop(env));
      }

      if(!(loop->running)) {
        break;
      }
    } while (more && !iotjs_environment_is_exiting(env));
  }

  return ret;
```
>!(loop->running) 表示模态对话框已经退出，可以回调上一级主循环了。

## 三、GUI 需要提供 Jerryscript 的绑定

要将 GUI 集成到 iotjs，GUI 必须要把对外提供的 AIP 全部绑定到 jerryscript。这个对 AWTK 来说只是举手之劳的事情，AWTK 通过提取注释来生成 IDL，再根据 IDL 来生成各种语言的绑定，这让绑定工作变得轻松，同时也降低了后期的维护成本。

AWTK-JS 这个项目提供了对 jerryscript 的绑定，我们把它编译成一个库，即可在 AWTK-iotjs 中使用了。

```
static int gui_app_start(int32_t lcd_w, int32_t lcd_h) {
  tk_init(lcd_w, lcd_h, APP_SIMULATOR, NULL, APP_ASSETS_ROOT);

  assets_init();
  awtk_js_init();
  main_loop()->running = TRUE;
  awtk_jerryscript_eval(AWTK_JS_FILE);

  tk_main_loop_run();

  return 0;
}
```

在启动 GUI 时，调用 awtk\_js\_init 初始化 AWTK 的 jerryscript 绑定，调用 awtk\_jerryscript\_eval 预先加载 awtk.js 文件。

> 完整例子请参考：https://github.com/zlgopen/awtk-iotjs