# 设置 CMake 最小版本
cmake_minimum_required(VERSION 3.5)
# 设置工程名
project(practice_3_4)
# 生成可执行文件
add_executable(3_43 3_43.cpp)
add_executable(3_44 3_44.cpp)

# 创建一个变量，名字叫SOURCE，它包含了所有的cpp文件
# set(SOURCE
#     3_43.cpp
#     3.44.cpp
# )