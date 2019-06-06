# awtk-iotjs

## 一、介绍

* 1. 关于 [iotjs](http://iotjs.net/)

> Internet of Things technologies connect "Things" and the things are getting smarter based on the connection. However there are still some barriers that each devices require its own application and/or services.

>IoT.js aims to provide inter-operable service platform in the world of IoT, based on web technology. The target of IoT.js is to run in resource constrained devices such as only few kilobytes of RAM available device. Thus it will supports very wide range of "Things".

> IoT.js is just taking the first steps and would like to get together with developers who has interests on our goal.

* 2. 关于 [AWTK](https://github.com/zlgopen/awtk)

>AWTK 全称 Toolkit AnyWhere，是 ZLG 开发的开源 GUI 引擎，旨在为嵌入式系统、WEB、各种小程序、手机和 PC 打造的通用 GUI 引擎，为用户提供一个功能强大、高效可靠、简单易用、可轻松做出炫酷效果的 GUI 引擎。

[awtk-iotjs](https://github.com/zlgopen/awtk-iotjs) 将 [awtk](https://github.com/zlgopen/awtk) 和 [iotjs](http://iotjs.net/) 有机结合起来，用 javascript 打通 GUI、网络和硬件，完全采用 javascript 开发物联网应用程序。

## 二、编译

* 下载编译 iotjs

```
git clone https://github.com/pando-project/iotjs.git
cd iotjs
./tools/build.py
cd -
```

* 下载编译 awtk

```
git clone https://github.com/zlgopen/awtk.git
cd awtk
scons
cd -
```

* 下载编译 awtk-js

```
git clone https://github.com/zlgopen/awtk-js.git
cd awtk-js
git clone https://github.com/jerryscript-project/jerryscript.git 3rd/jerryscript
scons
cd -
```

* 下载编译 awtk-iotjs

准备工作：
> 目前我不知道如何在 module.json 中指定编译参数，所以只好修改 iotjs/CMakeLists.txt 了。请在倒数第二行增加下面这行代码。

```
include(../awtk-iotjs/awtk-module/awtk.cmake)
```

下载编译：

```
git clone https://github.com/zlgopen/awtk-iotjs.git
cd awtk-iotjs
./build.sh
```

> 请确认以上项目均在同一个目录。

## 三、运行 DEMO

```
./run.sh demos/buttons.js
```

## 四、开发

在开发时可以使用：

* iotjs 提供的模块。
* awtk-js 提供的 GUI 控件。
* 其它第三方模块。

与 awtk-js 主要差异是需要加载并初始化 awtk：

```
require('awtk').init(320, 480);
```

完整示例：

```c
require('awtk').init(320, 480);

function applicationInit() {
  var win = TWindow.create(null, 0, 0, 0, 0); 
  var ok = TButton.create(win, 0, 0, 0, 0); 

  ok.setText("ok");
  ok.setSelfLayoutParams("center", "middle", "50%", "30");

  ok.on(TEventType.CLICK, function(evt) {
    var e = TPointerEvent.cast(evt);
    console.log("on click: " + e.x + " " + e.y);

    return TRet.OK;
  }); 

  win.layout();
}

applicationInit()
```

## 五、已知问题

* 只支持 Linux 系统 (Ubuntu >= 16)。
* 未 awtk-linux-fb 上验证，可能修改一下脚本。

> 理论上 Windows 平台也是可以的，但是 iotjs 没编译过。
