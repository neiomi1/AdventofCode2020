#include <fstream>
#include <chrono>
#include <iostream>

#include "Day_09.h"
#include "Day_09.cpp"

int main()
{
	auto maxset = MaxSet<int>(25);
	maxset.read_input("../../../../Day_09/input.txt");

	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_09\\execution_times.txt" };
	auto start = std::chrono::high_resolution_clock::now();
	int answer_part_one = maxset.read_until_bad();
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Part one in: " << duration.count() << " microseconds.\n";

	std::cout << "Part one answer: " << answer_part_one << "\n";

	start = std::chrono::high_resolution_clock::now();
	int answer_part_two = maxset.find_bad_set();
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Part two calculated in: " << duration.count() << " microseconds.\n";
	
	std::cout << "Part two answer: " << answer_part_two << "\n";
	//
	//start = std::chrono::high_resolution_clock::now();
	//int answer_part_two = handheld.fix_run();
	//stop = std::chrono::high_resolution_clock::now();
	//duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	//file_time << "Part two calculated in: " << duration.count() << " microseconds.";
	//
	//std::cout << "Part two answer: " << answer_part_two << "\n";

}
