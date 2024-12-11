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

class Rule {
public:
	virtual ~Rule() = default;

	virtual int match(const std::string& input, int index, bool root = false) = 0;
};

class Simple_Rule final: public Rule {
public:
	Simple_Rule(const char& letter);

	~Simple_Rule() = default;

	int match(const std::string& input, int index, bool root = false) override;

private:
	char letter_;
};

class Combine_Rule final: public Rule {
public:
	Combine_Rule(std::unordered_map<int, std::unique_ptr<Rule>>* map);

	Combine_Rule(std::unordered_map<int, std::unique_ptr<Rule>>* map, std::vector<int>& list);

	//Combine_Rule(const Combine_Rule&) = default;

	~Combine_Rule() = default;

	void add_rule(std::vector<int>& list);

	int match(const std::string& input, int index, bool root = false) override;

private:
	std::vector<std::vector<int>> rules_;
	std::unordered_map<int, std::unique_ptr<Rule>>* map_;
};


class Messages {
public:
	Messages(const std::string& filepath);

	void parse();

	int part_one(int starting_rule);

private:
	std::string filepath_;
	std::unordered_map<int, std::unique_ptr<Rule>> rules_{};
	std::vector<std::string> input_{};
};