#include "awtk.h"
#include "awtk_js.h"
#include "iotjs_def.h"
#include "jerryscript-ext/handler.h"
#include "jerry_script_helper.h"

extern ret_t assets_init(void);

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

const char* s_boot_script = "var exports = {}";

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

/*for modal dialog*/
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
}


static ret_t tk_main_loop_run(void) {
  main_loop()->run = main_loop_iotjs_run;

  jerry_script_eval_buff(s_step_script, strlen(s_step_script), "step.js", TRUE);
  return RET_OK;
}

static int gui_app_start(int32_t lcd_w, int32_t lcd_h) {
  tk_init(lcd_w, lcd_h, APP_SIMULATOR, NULL, APP_ASSETS_ROOT);
  tk_ext_widgets_init();

  assets_init();
  awtk_iotjs_jerryscript_init();

  main_loop()->running = TRUE;
  log_debug("AWTK_JS_FILE:%s\n", AWTK_JS_FILE);
  jerry_script_eval_buff(s_boot_script, strlen(s_boot_script), "iotjs_boot.js", TRUE);
  jerry_script_eval_file(AWTK_JS_FILE, TRUE);

  tk_main_loop_run();

  return 0;
}

JS_FUNCTION(awtk_init) {
  int32_t lcd_w = 0;
  int32_t lcd_h = 0;
  DJS_CHECK_ARGS(2, number, number);

  lcd_w = JS_GET_ARG(0, number);
  lcd_h = JS_GET_ARG(1, number);

  gui_app_start(lcd_w, lcd_h);

  return jerry_create_undefined();
}

jerry_value_t InitAwtkNativeModule() {
  jerry_value_t m = jerry_create_object();

  iotjs_jval_set_method(m, "init", awtk_init);
  iotjs_jval_set_property_string_raw(m, "awtkjs", AWTK_JS_FILE);
  iotjs_jval_set_property_string_raw(m, "resroot", APP_ASSETS_ROOT);

  jerryx_handler_register_global((const jerry_char_t*)"awtk_main_loop_step", wrap_awtk_main_loop_step);

  return m;
}
