cmake_minimum_required(VERSION 3.10)

project(webcalculator VERSION 0.1.0)
# 说明./epoll_lib下面还有CMakeLists.txt文件让cmake去读
add_subdirectory(./epoll_lib)

add_subdirectory(./src)


