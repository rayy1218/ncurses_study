cmake_minimum_required(VERSION 3.19)
project(snake)

set(CMAKE_CXX_STANDARD 14)

file(GLOB SRC src/*.hpp src/*.cpp)
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(snake ${SRC})
target_link_libraries(snake ${CURSES_LIBRARIES})