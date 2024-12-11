#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>

#include "../Day_01/Day_01.h"


TEST_CASE("test input", "[classic]")
{
	std::vector<int> entries;
	read_entries("../Day_01/test_input_01.txt", entries);
	REQUIRE(find_pair(2020, entries) == 514579);
	REQUIRE(find_triple(2020, entries) == 241861950);

#if defined(CATCH_CONFIG_ENABLE_BENCHMARKING)
	BENCHMARK("PAIR 2020") {
		 find_pair(2020, entries);
	};
	
	BENCHMARK("TRIPLE 2020") {
		 find_triple(2020, entries);
	};
#endif
};

TEST_CASE("Actual input", "[classic]")
{
	std::vector<int> entries;
	read_entries("../Day_01/input.txt", entries);
	CHECK(find_pair(2020, entries) == 100419);
	CHECK(find_triple(2020, entries) == 265253940);

	//BENCHMARK("PAIR 2020") {
	//	return find_pair(2020, entries);
	//};
	//
	//BENCHMARK("TRIPLE 2020") {
	//	return find_triple(2020, entries);
	//};
};


