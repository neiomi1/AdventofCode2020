#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>

#include "Day_19.h"

int main()
{
	auto messages = Messages("../../../../Day_19/input.txt");

	messages.parse();

	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_19\\execution_times.txt" };
	auto start = std::chrono::high_resolution_clock::now();
	auto answer_part_one = messages.part_one(0);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Part one calculated in: " << duration.count() << " microseconds.\n";

	std::cout << "Part one answer: " << answer_part_one << "\n";

	//start = std::chrono::high_resolution_clock::now();
	//auto answer_part_two = tickets.part_two();
	//stop = std::chrono::high_resolution_clock::now();
	//duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	//file_time << "Part two calculated in: " << duration.count() << " microseconds.";
	//
	//std::cout << "Part two answer: " << answer_part_two << "\n";

   
}