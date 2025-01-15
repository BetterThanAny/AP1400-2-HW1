#!/bin/bash

# 启用 'set -e'，遇到错误时立即退出
set -e

# 创建并进入 build 目录
mkdir build
cd build

# 运行 cmake 和 make
cmake ..
make && ./main

# 返回上一目录并删除 build 目录
cd ..
rm -rf build
