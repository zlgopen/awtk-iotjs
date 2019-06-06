#include "awtk.h"
#include "awtk_js.h"
#include "iotjs_def.h"
#include "jerryscript-ext/handler.h"

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

static ret_t tk_main_loop_run(void) {
  awtk_jerryscript_eval_script(s_step_script, strlen(s_step_script));

  return RET_OK;
}

static int gui_app_start(int32_t lcd_w, int32_t lcd_h) {
  tk_init(lcd_w, lcd_h, APP_SIMULATOR, NULL, APP_ASSETS_ROOT);

  assets_init();
  awtk_js_init();
  main_loop()->running = TRUE;
  awtk_jerryscript_eval(AWTK_JS_FILE);

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
