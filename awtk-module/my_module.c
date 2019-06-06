#include "iotjs_def.h"

jerry_value_t InitMyNativeModule() {
  jerry_value_t m = jerry_create_object();

  iotjs_jval_set_property_string_raw(m, "awtkjs", AWTK_JS_FILE);
  iotjs_jval_set_property_string_raw(m, "resroot", APP_ASSETS_ROOT);

  return m;
}
