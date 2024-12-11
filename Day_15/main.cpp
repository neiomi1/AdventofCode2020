#include <fstream>
#include <chrono>
#include <iostream>

#include "Day_15.h"

int main()
{
	auto game = Memory_game("../../../../Day_15/input.txt");

	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_15\\execution_times.txt" };
	auto start = std::chrono::high_resolution_clock::now();
	auto answer_part_one = game.part_one(2020);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Part one calculated in: " << duration.count() << " microseconds.\n";

	std::cout << "Part one answer: " << answer_part_one << "\n";

	start = std::chrono::high_resolution_clock::now();
	int answer_part_two = game.part_one(30000000);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Part two calculated in: " << duration.count() << " microseconds.";
	
	std::cout << "Part two answer: " << answer_part_two << "\n";

}
