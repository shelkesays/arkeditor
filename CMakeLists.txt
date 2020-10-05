# Terminal based Editor implementation in C++
# Copyright 2020 Octopi Labs.
# License under the MIT License. See the LICENSE file.

# This is a CMake for ArkEditor
cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(ArkEditor VERSION 0.1.0)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Wextra -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /WX /EHsc")
endif()

# Add project specific subdirectories 
add_subdirectory(src)
