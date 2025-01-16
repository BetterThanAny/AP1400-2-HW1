#!/bin/bash

# 启用 'set -e'，遇到错误时立即退出
set -e

# 创建并进入 build 目录
mkdir build
cd build

# 运行 cmake 和 make
cmake ..
# 在debug模式下构建时启用调试信息
# cmake .. -DCMAKE_CXX_FLAGS="-g"
make && ./main
#make && gdb ./main 

# 返回上一目录并删除 build 目录
cd ..
rm -rf build
