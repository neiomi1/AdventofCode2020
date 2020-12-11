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

class Ferry {
public:
	Ferry(const std::string& filepath);

	void read_input(const std::string& filepath);

	int check_seat_simple(int x, int y);

	int check_seat(int x, int y);

	bool simulate_simple_round();

	bool simulate_round();

	void print();

	int part_one();

	int part_two();

private:
	std::vector<std::vector<int>> current_seat_map_{};
	int width_ = 0;
	int height_ = 0;
	int occupied_ = 0;
	const std::string filepath_;
};
