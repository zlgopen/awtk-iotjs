# awtk-linux-fb

为linux framebufer编译稍微麻烦一点：


* 下载编译 iotjs

> 嵌入式版本，要修改工具链相关参数，请参考iotjs的文档。

```
git clone https://github.com/pando-project/iotjs.git
cd iotjs
./tools/build.py
cd -
```

* 下载 awtk

```
git clone https://github.com/zlgopen/awtk.git
```

* 下载编译 awtk-linux-fb

> 嵌入式版本，要修改SConstruct中工具链和tslib相关参数，请参考awtk-linux-fb的README.md。

```
git clone https://github.com/zlgopen/awtk-linux-fb.git
cd awtk-linux-fb
scons
release.sh
cd -
```

* 下载编译 awtk-js

> 嵌入式版本，要修改SConstruct中工具链参数，请参考awtk-linux-fb的README.md。

```
git clone https://github.com/zlgopen/awtk-js.git
cd awtk-js
git clone https://github.com/jerryscript-project/jerryscript.git 3rd/jerryscript
scons
cd -
```

* 下载 awtk-iotjs

```
git clone https://github.com/zlgopen/awtk-iotjs.git
```

* 启用linux fb特有的配置，并编译。

```
cd awtk-iotjs/awtk-module
mv awtk_linux_fb.cmake awtk.cmake
mv modules_linux_fb.json modules.json
cd -
./build.sh
```

* 拷贝相关文件。

```
mkdir awtk-linux-fb/release/js
cp awtk-js/src/awtk.js awtk-linux-fb/release/js
cp awtk-iotjs/demos/button.js awtk-linux-fb/release/js
cp iotjs/build/x86_64-linux/debug/bin/iotjs  awtk-linux-fb/release/bin
```

然后将 awtk-linux-fb/release 拷贝到开发板。

> 以上只大体思路，请酌情修改。

