# CMakeList.txt : CMake project for AdventofCodeDay9, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (AdventofCodeDay19 "Day_19.cpp" "Day_19.h" "main.cpp" "input_loop.txt")

# TODO: Add tests and install targets if needed.
target_compile_options(AdventofCodeDay19 PRIVATE /W4 /WX /permissive-)