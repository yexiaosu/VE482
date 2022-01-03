cmake_minimum_required(VERSION 3.20)
project(hw3 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(hw3
        h3.c
        list.c
        list.h)
