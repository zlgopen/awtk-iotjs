#!/bin/bash

source config.env

${IOTJS_ROOT}/tools/build.py --external-modules=${CWD}/awtk-module --cmake-param=-DENABLE_MODULE_AWTK=ON --cmake-param=-DJERRY_GLOBAL_HEAP_SIZE=4906 --cmake-param=-DJERRY_CPOINTER_32_BIT=1 


