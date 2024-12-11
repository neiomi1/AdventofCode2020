
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (Day01Tests "Day_01_test.cpp" )

add_executable (Day08Tests "Day_08_test.cpp" "../Day_08/Day_08.cpp")

# TODO: Add tests and install targets if needed.
#target_compile_definitions(Day01Tests PUBLIC CATCH_CONFIG_ENABLE_BENCHMARKING)
target_compile_features(Day01Tests PRIVATE cxx_std_20)
target_link_libraries(Day01Tests PUBLIC Catch2::Catch2)
catch_discover_tests(Day01Tests EXTRA_ARGS -s)


target_compile_features(Day08Tests PRIVATE cxx_std_20)
target_link_libraries(Day08Tests PUBLIC Catch2::Catch2)
catch_discover_tests(Day08Tests EXTRA_ARGS -s)