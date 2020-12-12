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

struct Instruction {
	char id;
	int amount;
};

class Ferry {
public:
	Ferry(const std::string& filepath);

	void read_input(const std::string& filepath);

	void execute(const Instruction& instruction, bool enable_waypoint = false);

	void reset();

	int part_one();

	int part_two();

private:
	int x_ = 0;
	int y_ = 0;
	const std::vector<std::pair<int, int>> dirs = { {0,1},{1,0},{0,-1}, {-1,0}};
	std::pair<int, int> waypoint_ = { 10,1 };
	int dir = 1;
	std::vector<Instruction> instructions_;
	const std::string filepath_;
};
