#!/bin/bash

source config.env

${IOTJS_ROOT}/tools/build.py --external-modules=./awtk-module --cmake-param=-DENABLE_MODULE_AWTK=ON

#${IOTJS_ROOT}/build/x86_64-linux/debug/bin/iotjs user.js

