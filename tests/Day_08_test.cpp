#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>

#include "../Day_08/Day_08.h"


TEST_CASE("test input", "[classic]")
{
	auto handheld = GameConsole("../../../../Day_08/test_input_01.txt");
	CHECK(handheld.run_until_loop() == 5);
	CHECK(handheld.fix_run() == 8);
};

TEST_CASE("input") {
	auto handheld = GameConsole("../../../../Day_08/input.txt");
	CHECK(handheld.run_until_loop() == 1797);
	CHECK(handheld.fix_run() == 1036);

	BENCHMARK("Loop detection") {
		handheld.run_until_loop();
	};

	BENCHMARK("Loop removal") {
		handheld.fix_run();
	};
}