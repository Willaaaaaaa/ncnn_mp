# ncnn-mp

**ncnn-mp** 是一个在 Micropython 平台上使用 [ncnn](https://github.com/Tencent/ncnn) 的扩展模块，提供了 **ncnn C API** 的绑定，让你在嵌入式设备（如 ESP32、STM32 等）上直接运行 ncnn 推理。

## 特性
- 基于 **ncnn C API**，轻量封装，方便移植。
- 可在支持 Micropython 的平台直接调用 ncnn 推理。

## 依赖
- [Micropython](https://micropython.org/)
- [ncnn](https://github.com/Tencent/ncnn)
- CMake/GNU Make

## 构建
MicroPython 针对不同的端口可能需要不同的构建工具，以下列举一些端口的示例供参考：

### Linux: 使用 Make
1. ncnn
```bash
mkdir build && cd build
# Example: a relatively feature-rich configuration
cmake -DCMAKE_BUILD_TYPE=Release -DNCNN_OPENMP=OFF -DNCNN_SIMPLEOMP=ON -DNCNN_VULKAN=ON -DNCNN_BUILD_BENCHMARK=OFF -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_INSTALL_PREFIX=./install ..
make -j4
make install
```
2. mpy
```bash
cd micropython/ports/unix/
make -C ../../mpy-cross -j4
make submodules -j4
make USER_C_MODULES=../../../modules USE_VULKAN=1 -j4
./build-standard/micropython ../../../examples/main.py
```

> 如果你需要进行 debug ，请将 `CMAKE_BUILD_TYPE` 改为 `DEBUG` ，并使用 `make USER_C_MODULES=../../../modules USE_VULKAN=1 NCNN_INSTALL_PREFIX=../../../ncnn/build-debug/install DEBUG=1 COPT=-O0 -j4` 这条命令。

### esp32-s3: 使用 CMake

这里应该是交叉编译，以 Linux 操作系统为例：

0. 准备工具链：`esp-idf` sdk
```shell
git clone https://github.com/espressif/esp-idf
cd esp-idf
```
根据 Micropython 的官方文档，我们必须使用 `esp-idf` 的一些特定版本。具体支持的版本[点击可得](https://github.com/micropython/micropython/blob/744270ac1b9ed3929cd41d1a6e1f6ea0e785745d/ports/esp32/README.md?plain=1#L33-L34) （这个链接更新于 2025.08.13）。查看最新的支持版本请在[这个文档]((https://github.com/micropython/micropython/blob/master/ports/esp32/README.md))中进行搜索查找。
```shell
git checkout v5.4.2
git submodule update --init --recursive
sh ./install.sh esp32s3
source export.sh
```

1. ncnn
```bash
cd ncnn
mkdir build-esp32s3 && cd build-esp32s3
# You should add configs here to minimize your ncnn lib
cmake -DCMAKE_TOOLCHAIN_FILE=../../toolchains/esp32s3.toolchain.cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_INSTALL_PREFIX=./install ..
make -j4
make install
```

2. micropython
```bash
cd micropython/ports/esp32
make -C ../../mpy-cross -j4
make submodules BOARD=ESP32_GENERIC_S3 -j4
idf.py -D MICROPY_BOARD=ESP32_GENERIC_S3 -D USER_C_MODULES=../../../../modules/ncnn_mp/micropython.cmake -D NCNN_INSTALL_PREFIX=../../../../ncnn/build-esp32s3/install build
```

3. 烧录
```bash
idf.py -p /dev/ttyACM0 erase-flash  # [optional]擦除开发板整个 Flash 芯片上的内容
idf.py -p /dev/ttyACM0 flash
idf.py -p /dev/ttyACM0 monitor  # 也可以 tio /dev/ttyACM0
```

参考: 
- esp-idf官方指导: https://docs.espressif.com/projects/esp-idf/zh_CN/stable/esp32s3/get-started/index.html
- 如果你使用 wsl: https://learn.microsoft.com/zh-cn/windows/wsl/connect-usb#attach-a-usb-device