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

class Ticket_ranges {
public:
	Ticket_ranges(const std::string& filepath);

	bool contains(int n);

	bool valid_ticket(std::vector<int>& ticket);

	std::vector<int> string_to_ticket(const std::string& string);

	bool trunctuate(std::unordered_map<std::string, std::vector<int>>& possible_indexes);

	uint64_t part_one();

	uint64_t part_two();

private:
	std::unordered_map<std::string, std::vector<std::pair<int, int>>> input_;
	std::vector<std::pair<int, int>> ranges_;
	std::string filepath_;
};