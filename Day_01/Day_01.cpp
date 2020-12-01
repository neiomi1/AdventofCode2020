// AdventofCodeDay1.cpp : Defines the entry point for the application.
//

#include "Day_01.h"
#include <vector>
#include <fstream>
#include <algorithm>

int num_entries = 0;
std::vector<int> entries;

void read_entries(const std::string& filename) {
	auto file = std::ifstream{ "..\\..\\..\\..\\Day_01\\" + filename };
	int current;
	while (file >> current) {
		entries.push_back(current);
		num_entries++;
	}
	std::sort(entries.begin(), entries.end(), std::greater<int>());
	//std::cout << entries.size();
}

int find_pair(int sum_goal) {
	for (int i = 0; i < num_entries; i++) {
		for (int j = i + 1; j < num_entries; j++) {
			int temp_sum = entries[i] + entries[j];
			if (temp_sum > sum_goal) {
			continue;
			}
			if (temp_sum == sum_goal) {
				return entries[i] * entries[j];
			}
		}
	}
	return NULL;
}

int find_triple(int sum_goal) {
	for (int i = 0; i < num_entries; i++) {
		for (int j = i + 1; j < num_entries; j++) {
			for (int k = j + 1; k < num_entries; k++) {
				int temp_sum = entries[i] + entries[j] + entries[k];
				if (temp_sum > sum_goal) {
					continue;
				}
				if (temp_sum == sum_goal) {
					return entries[i] * entries[j] * entries[k];
				}
			}
		}
	}
	return NULL;
}


int main()
{
	read_entries("input.txt");
	std::cout << "Pair Multiplication: " << find_pair(2020) << "\n";
	std::cout << "Triple Multiplcation: " << find_triple(2020) << "\n";
}
