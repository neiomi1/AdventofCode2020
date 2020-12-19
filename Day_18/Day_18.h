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
#include <regex>

#include <unordered_map>

class Calculator {
public:
	Calculator(const std::string& input);

	uint64_t calculate(int pos);

private:
	std::string input_;
};


class Homework {
public:
	Homework(const std::string& filepath);

	uint64_t sum_all_answers();

private:
	std::string filepath_;
};