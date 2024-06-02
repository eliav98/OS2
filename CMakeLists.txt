cmake_minimum_required(VERSION 3.25)
project(ex2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(examples)

add_executable(ex2
        src/uthreads.h)
