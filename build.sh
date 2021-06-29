#!/bin/bash

source config.env

${IOTJS_ROOT}/tools/build.py --external-modules=${CWD}/awtk-module --cmake-param=-DENABLE_MODULE_AWTK=ON --jerry-heaplimit=4096 \
  --jerry-debugger --cmake-param=-DWITH_TEXT_BIDI=1


