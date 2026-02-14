cmake_minimum_required(VERSION 3.20)

project(prototype C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-finput-charset=UTF-8 -fexec-charset=UTF-8)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main
    src/main.c
    src/ClientManager.c
    src/display.c
)

target_include_directories(main PRIVATE include)