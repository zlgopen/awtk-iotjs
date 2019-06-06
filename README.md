# awtk-iotjs

## 编译

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

修改 iotjs/CMakeLists.txt

在倒数第二行增加:

```
include(../awtk-iotjs/awtk-module/awtk.cmake)
```


```
git clone https://github.com/zlgopen/awtk-iotjs.git
cd awtk-iotjs
./build.sh
```

## 运行

```
./run.sh demos/buttons.js
```
