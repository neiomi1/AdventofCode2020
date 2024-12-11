# CMakeList.txt : CMake project for AdventofCodeDay9, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (AdventofCodeDay13 "Day_13.cpp" "Day_13.h" "main.cpp")

# TODO: Add tests and install targets if needed.
target_compile_options(AdventofCodeDay13 PRIVATE /W4 /WX /permissive-)