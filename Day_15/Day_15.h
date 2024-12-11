#pragma once

#include <string>
#include <set>
#include <queue>
#include <algorithm>
#include <istream>
#include <fstream>
#include <chrono>
#include <iostream>
#include <unordered_map>

class Memory_game {
public:
	Memory_game(const std::string& filepath);

	void reset();

	void read_start();

	void simulate_round();

	int part_one(int target);

private:
	int round_ = 1;
	std::vector<int> memory_;
	int last_number_ = 0;
	std::string filepath_;
	bool first_time_ = false;
};
