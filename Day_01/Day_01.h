// AdventofCodeDay1.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

// TODO: Reference additional headers your program requires here.
inline void read_entries(const std::string& filename, std::vector<int>& entries) {
	auto file = std::ifstream{ "..\\..\\..\\..\\Day_01\\" + filename };
	int current;
	while (file >> current) {
		entries.push_back(current);
	}
	std::sort(entries.begin(), entries.end());
}

inline int find_pair(int sum_goal, std::vector<int>& entries) {
	for (int i = 0; i < entries.size(); i++) {
		for (int j = i + 1; j < entries.size(); j++) {
			int temp_sum = entries[i] + entries[j];
			if (temp_sum > sum_goal) {
				break;
			}
			if (temp_sum == sum_goal) {
				return entries[i] * entries[j];
			}
		}
		if (entries[i] > sum_goal) {
			break;
		}
	}
	return -1;
}
inline int find_triple(int sum_goal, std::vector<int>& entries) {
	for (int i = 0; i < entries.size(); i++) {
		for (int j = i + 1; j < entries.size(); j++) {
			for (int k = j + 1; k < entries.size(); k++) {
				int temp_sum = entries[i] + entries[j] + entries[k];
				if (temp_sum > sum_goal) {
					break;
				}
				if (temp_sum == sum_goal) {
					return entries[i] * entries[j] * entries[k];
				}
			}
			if (entries[i] + entries[j] > sum_goal) {
				break;
			}
		}
		if (entries[i] > sum_goal) {
			break;

		}
	}
	return -1;
}