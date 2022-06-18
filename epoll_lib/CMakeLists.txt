set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
# 下面是将这个两个cpp编译成静态连接库
add_library(clientutility STATIC client_utility.cpp)
add_library(serverutility STATIC server_utility.cpp)
