# CMakeList.txt : CMake project for AdventofCodeDay9, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (AdventofCodeDay17 "Day_17.cpp" "Day_17.h" "main.cpp")

# TODO: Add tests and install targets if needed.
target_compile_options(AdventofCodeDay17 PRIVATE /W4 /WX /permissive-)