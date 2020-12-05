# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.10)

project ("AdventofCode2020")

# https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include sub-projects.
add_subdirectory ("Day_01")
add_subdirectory ("Day_02")
add_subdirectory ("Day_03")
add_subdirectory ("Day_04")
add_subdirectory ("Day_05")