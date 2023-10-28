cmake_minimum_required(VERSION 3.0)
project(library)

add_library(asio INTERFACE)
target_include_directories(asio SYSTEM INTERFACE ${CMAKE_SOURCE_DIR}/external/asio/asio/include)
add_subdirectory(external/wxWidgets)

add_executable(client src/client/main.cpp)
add_executable(server src/server/main.cpp)

set_property(TARGET client PROPERTY CXX_STANDARD 17)
set_property(TARGET server PROPERTY CXX_STANDARD 17)

target_compile_definitions(client PRIVATE ASIO_STANDALONE)
target_link_libraries(client wx::core wx::base asio)
target_link_libraries(server asio)
