cmake_minimum_required(VERSION 3.25)
project(ex2 CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Optionally set the build type (Release or Debug)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Include directories
include_directories(src)

# Add individual source files to avoid multiple definitions
add_executable(ex2
        src/main.cpp
        src/uthreads.cpp
        src/Thread.cpp
        src/ThreadManager.cpp
        )

# Set different compile options based on the build type
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set_target_properties(ex2 PROPERTIES LINKER_LANGUAGE CXX)
