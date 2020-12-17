#include <fstream>
#include <chrono>
#include <iostream>

#include "Day_17.h"

int main()
{
	auto conway = Cube_map("../../../../Day_17/iron_input.txt");
	
	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_17\\execution_times.txt" };
	auto start = std::chrono::high_resolution_clock::now();
	auto answer_part_one = conway.part_one();
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Part one calculated in: " << duration.count() << " microseconds.\n";
	
	std::cout << "Part one answer: " << answer_part_one << "\n";
   	
	start = std::chrono::high_resolution_clock::now();
	auto answer_part_two = conway.part_two();
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Part two calculated in: " << duration.count() << " microseconds.";
	
	std::cout << "Part two answer: " << answer_part_two << "\n";
   
}
