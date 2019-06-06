#!/bin/bash

source config.env

if [ "$1" == "" ]; then
  JS_FILE="demos/button.js"
else
  JS_FILE="$1"
fi

${IOTJS_ROOT}/build/x86_64-linux/debug/bin/iotjs "$JS_FILE"

