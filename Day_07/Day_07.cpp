

#include "Day_07.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <unordered_map>
#include <sstream>
#include <regex>
#include <unordered_set>

using Held_by_map = std::unordered_map<std::string, std::vector<std::string>>;
using Contains_map = std::unordered_map<std::string, std::unordered_map<std::string, int>>;

void read_entries(const std::string& filename, Held_by_map& held_by, Contains_map& contains) {
	auto file = std::ifstream{ "..\\..\\..\\..\\Day_07\\" + filename };
	std::string line;
	std::regex match_bags = std::regex("([a-z]+ [a-z]+ bag)");
	std::regex match_amount = std::regex("([0-9]+)");
	while (std::getline(file, line)) {
		std::vector<int> temp_nums{};
		std::vector<std::string> temp_bags{};

		std::sregex_iterator bags(line.begin(), line.end(), match_bags), end_bags;
		for (; bags != end_bags; bags++) {
			temp_bags.push_back((*bags)[0]);
		}
		std::sregex_iterator amount(line.begin(), line.end(), match_amount), end_amount;
		for (; amount != end_amount; amount++) {
			temp_nums.push_back(std::stoi((*amount)[0]));
		}

		for(int i = 1; i <= temp_nums.size(); i++){
			held_by[temp_bags[i]].push_back(temp_bags[0]);
			contains[temp_bags[0]][temp_bags[i]] = temp_nums[i-1];
		}
	}
}

int count_possible_bags(const std::string& bag, Held_by_map& held_by) {
	std::unordered_set<std::string> bags{bag};
	int n = 0;
	while (n < std::ssize(bags)) {
		n = (int)std::ssize(bags);
		for (auto it = bags.begin(); it != bags.end(); it++) {
			for (const auto& bag_unit : held_by[*it]) {
				if (!bags.contains(bag_unit)) {
					bags.insert(bag_unit);
				}
			}
		}
	}
	return (int)std::ssize(bags) - 1;
}

int count_contained_bags(const std::string& bag, Contains_map& contains) {
	int result = 0;
	std::vector<std::string> bags{bag};
	while (!bags.empty()) {
		int size = (int)std::ssize(bags);
		for (int i = 0; i <size; i++) {
			for (const auto& [bag_unit, amount] : contains[bags[i]]) {
				result += amount;
				for (int n = 0; n < amount; n++) {
					bags.push_back(bag_unit);
				}
			}
		}
		bags.erase(bags.begin(), bags.begin() + size);
	}
	return result;
}

int main()
{
	auto held_by = Held_by_map{};
	auto contains = Contains_map{};


	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_07\\execution_times.txt" };
	auto start = std::chrono::high_resolution_clock::now();
	read_entries("input.txt", held_by, contains);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Input read and parsed in: " << duration.count() << " microseconds.\n";
	
	start = std::chrono::high_resolution_clock::now();
	int answer_sum = count_possible_bags("shiny gold bag", held_by);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Sum of all bags containing calculated in: " << duration.count() << " microseconds.\n";
	
	std::cout <<"Sum of all bags containing: "<< answer_sum << "\n";
	
	start = std::chrono::high_resolution_clock::now();
	answer_sum = count_contained_bags("shiny gold bag", contains);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Number of all contained bags calculated in: " << duration.count() << " microseconds.";
	
	std::cout << "Number of all contained bags: " << answer_sum << "\n";
	
}
