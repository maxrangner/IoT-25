cmake_minimum_required(VERSION 3.20)

project(prototype C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main
    src/main.c
    src/ClientManager.c
)

target_include_directories(main PRIVATE include)