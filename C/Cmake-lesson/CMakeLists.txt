cmake_minimum_required(VERSION 3.10)
project(CMAKE_LESSON C)

set(CMAKE_C_STANDARD 99)                # chuẩn C99
set(CMAKE_BUILD_TYPE Debug)             # debug build
set(CMAKE_C_FLAGS_DEBUG "-g -O0")       # flag debug

include_directories(inc)

add_executable(app src/main.c src/test.c)