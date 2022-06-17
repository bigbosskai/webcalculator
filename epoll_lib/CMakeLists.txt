set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)
add_library(clientutility STATIC client_utility.cpp)
add_library(serverutility STATIC server_utility.cpp)
