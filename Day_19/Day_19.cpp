#include <sstream>
#include "Day_19.h"

Simple_Rule::Simple_Rule(const char& letter):letter_(letter){}

bool Simple_Rule::match(const std::string& input, int index)
{
	return input[index] == letter_;
}

Combine_Rule::Combine_Rule(std::unordered_map<int, std::unique_ptr<Rule>>& map,std::vector<int>& list): map_(map){
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

bool Combine_Rule::match(const std::string& input, int index)
{
	for (auto ruleset : rules_) {
		int ind = index;
		bool matches = true;
		for (auto rule : ruleset) {
			matches = matches && (*map_[rule]).match(input, ind);
		}
		if (matches) {
			return true;
		}
	}
	return false;
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
			int ruleint;
			char c;
			auto stream = std::istringstream{ line };
			stream >> rulenum >> c;
			std::vector<int> rules;
			while (stream >> ruleint) {
				rules.push_back(ruleint);
			}
			if (rules.empty()) {
				stream >> c;
				std::cout << rulenum << " " << c << "\n";
				rules_[rulenum] = std::make_unique<Rule>(Simple_Rule(c));
			}
			else {
				auto rule = Combine_Rule(rules_, rules);
				while (!rules.empty()) {
					rules.clear();
					while (stream >> ruleint) {
						rules.push_back(ruleint);
					}
					rule.add_rule(rules);
				}
				rules_[rulenum] = std::make_unique<Rule>(rule);
			}


		}
		else {
			input_.push_back(line);
		}
	}
}

int Messages::part_one(int starting_rule)
{
	int sum = 0;
	for (const auto& line : input_) {
		if ((*rules_[0]).match(line, starting_rule)) {
			sum++;
		}
	}
	return sum;
}
