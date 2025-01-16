
## 笔记

Docker 的配置与使用 (linux)
创建镜像(需要在 Dockerfile 文件所在的文件夹下进行操作，
我已经把gcc改为最新版本，旧版本无法创建镜像)

docker build -t ap14002hw .

启动镜像，并将 hw 所在的文件夹映射到镜像中

docker run -it -d --name AP1400HW -v ./:/home/hw ap14002hw /bin/bash

之后便可在 vscode 中直接连接到相应的 container 中直接进行编程

运行第二条命令报错如下：
docker run -it -d --name AP1400HW -v ./:/home/hw ap14002hw /bin/bash        
docker: Error response from daemon: create .: volume name is too short, 
names should be at least two alphanumeric characters.
See 'docker run --help'.

原因：使用了太短的卷名称，要求至少两个字母或数字字符，改为下面命令

docker run -it -d --name AP1400HW -v $(pwd):/home/hw ap14002hw /bin/bash

继续报错如下：
 docker run -it -d --name AP1400HW -v $(pwd):/home/hw ap14002hw /bin/bash    
docker: invalid reference format.
See 'docker run --help'.

原因：$(pwd) 语法在 Windows 的命令提示符（CMD）或 PowerShell 中无效。
它是 Linux 或 macOS 中的有效命令（我有一句麻麻批想讲）

docker run -it -d --name AP1400HW -v ${PWD}:/home/hw ap14002hw /bin/bash

运行上述命令后：
 docker run -it -d --name AP1400HW -v ${PWD}:/home/hw ap14002hw /bin/bash    
46d22e2d8aa9d851b3cba321de47bf1750916131b590a1c0ebc43220a5d444c3

上面一串代码是容器的 ID ，意味着 Docker 容器已经成功启动并在后台运行（因为最开始
build -t 表明可以后台运行）

之后便可在 vscode 中直接连接到相应的 container 中直接进行编程，注意文件在 
/home/hw 中

文件夹映射（bind mount）：在宿主机和容器之间同步文件，修改文件会双向反映，容器关闭不会丢失数据。
Docker 卷（volumes）：适合需要持久化存储的数据，数据不会因为容器的停止或删除而丢失。
如果你只是修改文件并希望它们持续保存在宿主机和容器之间同步，bind mount 是足够的。
如果你希望数据能在容器生命周期之外持久化，建议使用 Docker 卷。

```bash
gdb --version #查看是否安装gdb
```

没安装的话 `sudo apt install` 一下 

如果想在使用 cmake 构建项目时启用调试信息（即编译时使用 -g 选项）以下有两种方法
- 在 CMakeLists.txt 中添加 `set(CMAKE_BUILD_TYPE Debug)` 
- 把原来的 `cmake .. ` 改为 `cmake .. -DCMAKE_CXX_FLAGS="-g"` 

然后 `gdb ./main` 时给出下面的报错信息：

```  
Program received signal SIGSEGV, Segmentation fault.
0x00000000004093ac in std::vector<double, std::allocator<double> >::size (this=0x0)
    at /usr/local/include/c++/13.3.0/bits/stl_vector.h:993
993           { return size_type(this->_M_impl._M_finish - this->_M_impl._M_start); }
```
