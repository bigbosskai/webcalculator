include_directories(${PROJECT_SOURCE_DIR}/epoll_lib)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(client client.cpp)
add_executable(server server.cpp)

target_link_libraries(client clientutility)
target_link_libraries(server serverutility)


