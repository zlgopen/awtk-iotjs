#!/bin/bash

source config.env

${IOTJS_ROOT}/tools/build.py --external-modules=${CWD}/awtk-module --cmake-param=-DENABLE_MODULE_AWTK=ON


