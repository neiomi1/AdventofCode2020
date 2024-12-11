#pragma once


#include <string>
#include <set>
#include <queue>
#include <algorithm>
#include <istream>
#include <fstream>
#include <chrono>
#include <sstream>
#include <iostream>
#include <numeric>
#include <unordered_map>

class Adapters {
public:
	Adapters(const std::string& filepath);

	int part_one();

	uint64_t calculate_permutations(int size);

	uint64_t part_two();

private:
	std::vector<int> jolts_{ 0 };
	std::vector<std::vector<int>> jolt_groups_{};
	std::unordered_map<int, uint64_t> memory_{ {0,0}, {1,1},{2,1} };
};

