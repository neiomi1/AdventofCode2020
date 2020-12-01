// AdventofCodeDay1.cpp : Defines the entry point for the application.
//

#include "Day_01.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono>

int num_entries = 0;
std::vector<int> entries;

void read_entries(const std::string& filename) {
	auto file = std::ifstream{ "..\\..\\..\\..\\Day_01\\" + filename };
	int current;
	while (file >> current) {
		entries.push_back(current);
		num_entries++;
	}
	std::sort(entries.begin(), entries.end());
}

int find_pair(int sum_goal) {
	for (int i = 0; i < num_entries; i++) {
		for (int j = i + 1; j < num_entries; j++) {
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
	return NULL;
}

int find_triple(int sum_goal) {
	for (int i = 0; i < num_entries; i++) {
		for (int j = i + 1; j < num_entries; j++) {
			for (int k = j + 1; k < num_entries; k++) {
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
	return NULL;
}


int main()
{
	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_01\\execution_times.txt" };
	auto start = std::chrono::high_resolution_clock::now();
	read_entries("input.txt");
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Input read in " << duration.count() << " microseconds.\n";

	start = std::chrono::high_resolution_clock::now();
	std::cout << "Pair Multiplication: " << find_pair(2020) << "\n";
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Pair calculated in " << duration.count() << " microseconds.\n";

	start = std::chrono::high_resolution_clock::now();
	std::cout << "Triple Multiplcation: " << find_triple(2020) << "\n";
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Triple calculated in " << duration.count() << " microseconds.";

}
