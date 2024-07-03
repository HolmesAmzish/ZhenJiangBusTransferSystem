cmake_minimum_required(VERSION 3.10)

# 项目名称
project(BusTransportSystem)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 包含头文件目录
include_directories(include)

# 源文件列表
set(SOURCES
    src/main.cpp
    src/stop.cpp
    src/route.cpp
    src/user.cpp
    src/menu.cpp
)

# 生成可执行文件
add_executable(BusTransportSystem ${SOURCES})
