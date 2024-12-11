# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.10)

project ("AdventofCode2020")


# FetchTest-Library and enable unit tests
include(FetchContent)
FetchContent_Declare(
	catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG        v2.13.3
	TIMEOUT        10
)

FetchContent_GetProperties(catch2)
if(NOT catch2_POPULATED)
	message("Fetching catch2 library from github")
	FetchContent_Populate(catch2)
	set(CATCH_BUILD_TESTING   OFF CACHE BOOL "" FORCE)
	set(CATCH_INSTALL_DOCS    OFF CACHE BOOL "" FORCE)
	set(CATCH_INSTALL_HELPERS ON  CACHE BOOL "" FORCE)
	add_subdirectory(${catch2_SOURCE_DIR} ${catch2_BINARY_DIR})
	include(${catch2_SOURCE_DIR}/contrib/Catch.cmake)
	include(CTest)
endif()

enable_testing()

# https://cmake.org/cmake/help/latest/prop_tgt/CXX_STANDARD.html
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include sub-projects.
add_subdirectory ("TESTS")
add_subdirectory ("Day_01")
add_subdirectory ("Day_02")
add_subdirectory ("Day_03")
add_subdirectory ("Day_04")
add_subdirectory ("Day_05")
add_subdirectory ("Day_06")
add_subdirectory ("Day_07")
add_subdirectory ("Day_08")
add_subdirectory ("Day_09")
add_subdirectory ("Day_10")
add_subdirectory ("Day_11")
add_subdirectory ("Day_12")
add_subdirectory ("Day_13")
add_subdirectory ("Day_14")
add_subdirectory ("Day_15")
add_subdirectory ("Day_16")
add_subdirectory ("Day_17")
add_subdirectory ("Day_18")
add_subdirectory ("Day_19")