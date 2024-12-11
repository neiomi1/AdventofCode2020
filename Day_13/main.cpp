#include <fstream>
#include <chrono>
#include <iostream>

#include "Day_13.h"

int main()
{
	auto busHub = BusHub();

	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_13\\execution_times.txt" };
	auto start = std::chrono::high_resolution_clock::now();
	busHub.read_entries("../../../../Day_13/input.txt");
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Input read in: " << duration.count() << " microseconds.\n";

	start = std::chrono::high_resolution_clock::now();
	int answer_part_one = busHub.part_one();
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Part one calculated in: " << duration.count() << " microseconds.\n";
	
	std::cout << "Part one answer: " << answer_part_one << "\n";
	
	start = std::chrono::high_resolution_clock::now();
	uint64_t answer_part_two = busHub.part_two();
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Part two calculated in: " << duration.count() << " microseconds.";
	
	std::cout << "Part two answer: " << answer_part_two << "\n";
   

}
