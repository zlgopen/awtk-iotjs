#include "awtk.h"
#include "awtk_js.h"
#include "iotjs_def.h"

extern ret_t assets_init(void);

static void main_loop_step_on_timer(uv_timer_t* handle) {
  main_loop_step(main_loop());
  uv_timer_set_repeat(handle, 1);

  return;
}

static ret_t tk_main_loop_run(void) {
  static uv_timer_t s_awtk_mainloop_timer;
  uv_timer_init(uv_default_loop(), &s_awtk_mainloop_timer);
  uv_timer_start(&s_awtk_mainloop_timer, main_loop_step_on_timer, 16, 1);

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

  return m;
}
