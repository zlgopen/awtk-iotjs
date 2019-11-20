GET_FILENAME_COMPONENT(PROJ_ROOT "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)

SET(AWTK_ROOT ${PROJ_ROOT}/awtk)
SET(AWTK_JERRYSCRIPT_ROOT ${PROJ_ROOT}/awtk-jerryscript)
SET(APP_ASSETS_ROOT ${AWTK_ROOT}/demos)
SET(AWTK_JS_FILE ${AWTK_JERRYSCRIPT_ROOT}/src/js/awtk.js)
SET(AWTK_LINX_FB_ROOT ${PROJ_ROOT}/awtk-linux-fb)

MESSAGE("AWTK_ROOT=${AWTK_ROOT}")
MESSAGE("AWTK_JERRYSCRIPT_ROOT=${AWTK_JERRYSCRIPT_ROOT}")
MESSAGE("CMAKE_CURRENT_LIST_DIR=${CMAKE_CURRENT_LIST_DIR}")

SET( CMAKE_VERBOSE_MAKEFILE ON )
ADD_COMPILE_OPTIONS("-DAWTK_JS_FILE=\"${AWTK_JS_FILE}\"")
ADD_COMPILE_OPTIONS("-DAPP_ASSETS_ROOT=\"${APP_ASSETS_ROOT}\"")

LINK_DIRECTORIES("${AWTK_LINX_FB_ROOT}/build/lib" "${AWTK_JERRYSCRIPT_ROOT}/lib")
INCLUDE_DIRECTORIES("${AWTK_ROOT}/src/" "${AWTK_ROOT}/src/ext_widgets/" "${AWTK_JERRYSCRIPT_ROOT}/src/c")
