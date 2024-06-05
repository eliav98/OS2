cmake_minimum_required(VERSION 3.25)
project(ex2 CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SOURCES "src/*.cpp")

if (SOURCES)
    add_executable(ex2 ${SOURCES})
else()
    message(FATAL_ERROR "No source files found. Please check your directory structure.")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set_target_properties(ex2 PROPERTIES LINKER_LANGUAGE CXX)
