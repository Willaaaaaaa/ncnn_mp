# ncnn-mp

**ncnn-mp** 是一个在 Micropython 平台上使用 [ncnn](https://github.com/Tencent/ncnn) 的扩展模块，提供了 **ncnn C API** 的绑定，让你在嵌入式设备（如 ESP32、STM32 等）上直接运行 ncnn 推理。

## 特性
- 基于 **ncnn C API**，轻量封装，方便移植。
- 可在支持 Micropython 的平台直接调用 ncnn 推理。

## 依赖
- [Micropython](https://micropython.org/)
- [ncnn](https://github.com/Tencent/ncnn)
- CMake/GNU Make

