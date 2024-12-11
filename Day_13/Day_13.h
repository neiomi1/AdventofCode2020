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
#include <map>

class BusHub {
public:

	void read_entries(const std::string& filepath);

	int calculate_wait(int bus_ID);

	int part_one();

	uint64_t part_two();

private:
	std::vector<int> bus_IDs_;
	std::map<int, int> wait_time_;
	int starting_point_ = 0;
};