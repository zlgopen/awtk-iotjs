# 为 iotjs 开发原生模块

> [iotjs](https://github.com/pando-project/iotjs) 是三星开源的 javascript 物联网开发平台。它为 javascript 应用程序提供了访问硬件、网络、文件系统和异步化的能力，功能类似于 nodejs，但无论是代码体积还是内存需求，iotjs 都要小很多，是用 javascript 开发 iot 设备应用程序的首选。

>AWTK 全称 Toolkit AnyWhere，是 ZLG 开发的开源 GUI 引擎，旨在为嵌入式系统、WEB、各种小程序、手机和 PC 打造的通用 GUI 引擎，为用户提供一个功能强大、高效可靠、简单易用、可轻松做出炫酷效果的 GUI 引擎。

为 [iotjs](https://github.com/pando-project/iotjs) 开发原生模块，这篇 [官方的文档](https://github.com/pando-project/iotjs/wiki/Writing-New-Module) 是必须要读的，里面使用的 mymodule 例子是可以用的。在集成 [AWTK]() 到 [iotjs](https://github.com/pando-project/iotjs) 时，也需要写一个原生模块，实际情况与例子差别很大，遇到几个坑，折腾了大半天时间。这里记个笔记，供有需要的朋友参考。

## 一、修改模块的名称

如果模块的名称使用 mymodule 是没有问题的，但是 mymodule 是一个无意义的名称，无法表达实际模块的真实功能。我这里需要把模块改名为 awtk，可以按下列方式来做：

* 目录名使用 awtk-module

```
mkdir awtk-module
```

* 将 C 代码的源文件改名为 awtk_module.c，并将初始化函数改名 InitAwtkNativeModule。

* 创建 awtk-module/modules.json

```
{
  "modules": {
    "awtk": {
      "native_files": ["awtk_module.c"],
      "init": "InitAwtkNativeModule",
      "external_libs":["awtk-jerryscript", "jerryscript", "awtk", "assets", "glad", "gpinyin", "linebreak", "nanovg"], 
      "platforms": {
        "linux": {
          "external_libs":["SDL2", "gtk-3", "gdk-3", "sndio", "Xext", "X11", "stdc++", "dl", "m"]
        }   
      }   
    }
  }
}
```

* 修改编译脚本参数

```
tools/build.py --external-modules=awtk-module --cmake-param=-DENABLE_MODULE_AWTK=ON
```

> ENABLE\_MODULE\_ 一定要写实际模块的名称，如果忘记将 MYMODULE 修改成实际模块的名称，出现的错误让你完全不知道是什么情况。

## 二、编译参数

自己的模块免不了使用外部库，但是 modules.json 里可以指定库的名称，却不能指定库的路径和头文件的路径。做了尝试始终没有成功，后来只好自己写了一个 cmake 文件，在 iotjs 的 CMakeLists.txt 引用了。

awtk.cmake 的内容如下：

```
GET_FILENAME_COMPONENT(PROJ_ROOT "${CMAKE_CURRENT_LIST_DIR}/../../" ABSOLUTE)

SET(AWTK_ROOT ${PROJ_ROOT}/awtk)
SET(AWTK_JS_ROOT ${PROJ_ROOT}/awtk-js)
SET(APP_ASSETS_ROOT ${AWTK_ROOT}/demos)
SET(AWTK_JS_FILE ${AWTK_JS_ROOT}/src/awtk.js)

MESSAGE("AWTK_ROOT=${AWTK_ROOT}")
MESSAGE("AWTK_JS_ROOT=${AWTK_JS_ROOT}")
MESSAGE("AWTK_JS_ROOT=${CMAKE_CURRENT_LIST_DIR}")

SET( CMAKE_VERBOSE_MAKEFILE ON )
ADD_COMPILE_OPTIONS("-DAWTK_JS_FILE=\"${AWTK_JS_FILE}\"")
ADD_COMPILE_OPTIONS("-DAPP_ASSETS_ROOT=\"${APP_ASSETS_ROOT}\"")

LINK_DIRECTORIES("${AWTK_ROOT}/lib" "${AWTK_JS_ROOT}/lib")
INCLUDE_DIRECTORIES("${AWTK_ROOT}/src/" "${AWTK_ROOT}/src/ext_widgets/" "${AWTK_JS_ROOT}/src/jerryscript")
```

使用下面这行代码开启 verbose 模式，可以看到大量调试信息，有助于快速定位问题所在：

```
SET( CMAKE_VERBOSE_MAKEFILE ON )
```

然后在 CMakeLists.txt 里引用：

```
include(../awtk-iotjs/awtk-module/awtk.cmake)
include(cmake/iotjs.cmake)
```

> 一定要放在 iotjs.cmake 之前引用，否则无效。

## 三、放在独立的目录

将模块放在独立的目录中，管理起来方便一些，awtk-iotjs 是为 iotjs 写的模块，它依赖与 awtk 和 awtk-js，将在几个模块放在同级的目录。

* awtk
* awtk-js
* iotjs
* awtk-iotjs

编译脚本改为：

```
${iotjs_ROOT}/tools/build.py --external-modules=${CWD}/awtk-module --cmake-param=-DENABLE_MODULE_AWTK=ON
```

运行脚本改为：

```
if [ "$1" == "" ]; then
  JS_FILE="demos/button.js"
else
  JS_FILE="$1"
fi

${iotjs_ROOT}/build/x86_64-linux/debug/bin/iotjs "$JS_FILE"
```

> 完整例子请参考：https://github.com/zlgopen/awtk-iotjs
