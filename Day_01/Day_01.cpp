// AdventofCodeDay1.cpp : Defines the entry point for the application.
//

#include "Day_01.h"

#include <chrono>


int main()
{
	std::vector<int> entries;

	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_01\\execution_times.txt" };
	auto start = std::chrono::high_resolution_clock::now();
	read_entries("input.txt", entries);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Input read in " << duration.count() << " microseconds.\n";

	start = std::chrono::high_resolution_clock::now();
	std::cout << "Pair Multiplication: " << find_pair(2020, entries) << "\n";
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Pair calculated in " << duration.count() << " microseconds.\n";

	start = std::chrono::high_resolution_clock::now();
	std::cout << "Triple Multiplcation: " << find_triple(2020, entries) << "\n";
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Triple calculated in " << duration.count() << " microseconds.";

}
