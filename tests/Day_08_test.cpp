#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include "../Day_08/Day_08.h"


TEST_CASE("test input", "[classic]")
{
	auto handheld = GameConsole("../Day_08/test_input_01.txt");
	REQUIRE(handheld.run_until_loop() == 5);
	REQUIRE(handheld.fix_run() == 8);
};
