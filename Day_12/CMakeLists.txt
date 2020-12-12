# CMakeList.txt : CMake project for AdventofCodeDay9, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (AdventofCodeDay12 "Day_12.cpp" "Day_12.h" "main.cpp")

# TODO: Add tests and install targets if needed.
target_compile_options(AdventofCodeDay12 PRIVATE /W4 /WX /permissive-)