# awtk-iotjs

## 一、介绍

* 1.关于 [iotjs](http://iotjs.net/)

> Internet of Things technologies connect "Things" and the things are getting smarter based on the connection. However there are still some barriers that each devices require its own application and/or services.

>IoT.js aims to provide inter-operable service platform in the world of IoT, based on web technology. The target of IoT.js is to run in resource constrained devices such as only few kilobytes of RAM available device. Thus it will supports very wide range of "Things".

> IoT.js is just taking the first steps and would like to get together with developers who has interests on our goal.

* 2.关于 [AWTK](https://github.com/zlgopen/awtk)

>AWTK 全称 Toolkit AnyWhere，是 ZLG 开发的开源 GUI 引擎，旨在为嵌入式系统、WEB、各种小程序、手机和 PC 打造的通用 GUI 引擎，为用户提供一个功能强大、高效可靠、简单易用、可轻松做出炫酷效果的 GUI 引擎。

[AWTK-IOTJS](https://github.com/zlgopen/awtk-iotjs)将[AWTK](https://github.com/zlgopen/awtk)和[iotjs](http://iotjs.net/)有机结合起来，用javascript打通GUI、网络和硬件，极大的提高物联网应用程序的开发效率。


## 二、编译

* 下载编译iotjs

```
git clone https://github.com/pando-project/iotjs.git
cd iotjs
./tools/build.py
cd -
```

* 下载编译awtk

```
git clone https://github.com/zlgopen/awtk.git
cd awtk
scons
cd -
```

* 下载编译awtk-js

```
git clone https://github.com/zlgopen/awtk-js.git
cd awtk-js
git clone https://github.com/jerryscript-project/jerryscript.git 3rd/jerryscript
scons
cd -
```

* 下载编译awtk-iotjs

准备工作：
> 目前我不知道如何在module.json中指定编译参数，所以只好修改 iotjs/CMakeLists.txt了。请在倒数第二行增加下面这行代码。

```
include(../awtk-iotjs/awtk-module/awtk.cmake)
```

下载编译：


```
git clone https://github.com/zlgopen/awtk-iotjs.git
cd awtk-iotjs
./build.sh
```

## 三、运行DEMO

```
./run.sh demos/buttons.js
```
