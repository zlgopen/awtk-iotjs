GET_FILENAME_COMPONENT(PROJ_ROOT "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)

SET( CMAKE_VERBOSE_MAKEFILE ON )

SET(AWTK_ROOT ${PROJ_ROOT}/awtk)
SET(AWTK_JERRYSCRIPT_ROOT ${PROJ_ROOT}/awtk-jerryscript)
LINK_DIRECTORIES("${AWTK_ROOT}/lib" "${AWTK_JERRYSCRIPT_ROOT}/lib")
INCLUDE_DIRECTORIES("${AWTK_ROOT}/src/" "${AWTK_ROOT}/src/ext_widgets/" "${AWTK_JERRYSCRIPT_ROOT}/src/c")
