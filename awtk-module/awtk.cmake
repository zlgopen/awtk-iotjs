set(PROJ_ROOT /home/lixianjing/work/awtk-root)

set(AWTK_ROOT ${PROJ_ROOT}/awtk)
set(AWTK_JS_ROOT ${PROJ_ROOT}/awtk-js)
set(APP_ASSETS_ROOT ${AWTK_ROOT}/demos)
set(AWTK_JS_FILE ${AWTK_JS_ROOT}/src/awtk.js)

message("AWTK_ROOT=${AWTK_ROOT}")
message("AWTK_JS_ROOT=${AWTK_JS_ROOT}")

set( CMAKE_VERBOSE_MAKEFILE on )
add_compile_options("-DAWTK_JS_FILE=\"${AWTK_JS_FILE}\"")
add_compile_options("-DAPP_ASSETS_ROOT=\"${APP_ASSETS_ROOT}\"")

LINK_DIRECTORIES("${AWTK_ROOT}/lib" "${AWTK_JS_ROOT}/lib")
INCLUDE_DIRECTORIES("${AWTK_ROOT}/src/" "${AWTK_ROOT}/src/ext_widgets/" "${AWTK_JS_ROOT}/src/jerryscript")

