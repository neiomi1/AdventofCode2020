#include <sstream>
#include "Day_19.h"

Simple_Rule::Simple_Rule(const char& letter):letter_(letter){}

int Simple_Rule::match(const std::string& input, int index, bool root)
{
	if (input[index] == letter_) {
		return index+1;
	 }
	if (root) {
		return index + 1;
	}
	return -1;
}

Combine_Rule::Combine_Rule(std::unordered_map<int, std::unique_ptr<Rule>>* map): map_(map)
{
}

Combine_Rule::Combine_Rule(std::unordered_map<int, std::unique_ptr<Rule>>* map,std::vector<int>& list): map_(map){
	add_rule(list);
}

void Combine_Rule::add_rule(std::vector<int>& list)
{
	std::vector<int> ruleset;
	for (auto it = list.begin(); it != list.end(); it++) {
		ruleset.push_back(*it);
	}
	rules_.push_back(ruleset);
}

int Combine_Rule::match(const std::string& input, int index, bool root)
{
	for (auto ruleset : rules_) {
		int ind = index;
		for (auto rule : ruleset) {
			ind = (*(*map_)[rule]).match(input, ind);
			if (ind == -1) {
				break;
			}
			if (ind == std::size(input) && !root) {
				return ind;
			}
		}
		if(ind != -1) {
			return ind;
		}
	}
	return -1;
}

Messages::Messages(const std::string& filepath) : filepath_(filepath)
{
}

void Messages::parse()
{
	auto file = std::ifstream{ filepath_ };
	int rulenum;
	std::string line;
	while (std::getline(file, line)) {
		if (line.find(':') != std::string::npos) {
			std::string token;
			auto stream = std::istringstream{ line };
			std::vector<int> rules;
			auto rule  = Combine_Rule(&rules_) ;
			while (stream >> token) {
				if (token.find(":")!= std::string::npos) {
					//std::cout << token<<  "\n";
					rulenum = std::stoi(token.substr(0, token.size() - 1));
					//std::cout << rulenum;
				}
				else if (token.find("\"") != std::string::npos) {
					//std::cout << token[1];
					auto ptr = std::make_unique<Simple_Rule>(Simple_Rule(token[1]));
					rules_[rulenum] = std::move(ptr);
					break;
				}
				else if (token.find("|") != std::string::npos) {
					rule.add_rule(rules);
					rules.clear();
					//std::cout << " | ";
				}
				else {
					//std::cout << token << "\n";
					rules.push_back(std::stoi(token));
					//std::cout << std::stoi(token) << " ";
				}
			}
			//std::cout << "\n";
			if (!rules.empty()) {
				rule.add_rule(rules);
				rules.clear();
				auto ptr = std::make_unique<Combine_Rule>(rule);
				rules_[rulenum] = std::move(ptr);
			}
		}
		else {
			if (!line.empty()) {
				input_.push_back(line);
			}
		}
	}
}

int Messages::part_one(int starting_rule)
{
	int sum = 0;
	for (const auto& line : input_) {
		//std::cout << line << ": " << std::ssize(line) << " - " << (*rules_[starting_rule]).match(line, 0) << "\n";
		if ((*rules_[starting_rule]).match(line, 0, true) == std::ssize(line)) {
			std::cout << line << "\n";
			sum++;
		}
	}
	return sum;
}
