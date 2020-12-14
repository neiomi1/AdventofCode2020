#include <fstream>
#include <chrono>
#include <iostream>

#include "Day_14.h"

int main()
{
	//auto mask = BitInteger("XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X",2);
	//
	//auto num_0 = BitInteger();
	//
	//num_0.print();
	//
	//mask.print();
	//
	//num_0.mask(mask);
	//
	//num_0.print();
	//
	//
	//auto num_1 = BitInteger("000000000000000000000000000001100101",2);
	//
	//num_1.print();
	//
	//auto num_2 = BitInteger("000000000000000000000000000001000000",2);
	//
	//num_2.print();
	//
	//std::cout << num_1.to_integer() << " + " << num_2.to_integer()  << "\n";
	//
	//num_1 += num_2;
	//
	//num_1.print();
	//
	//std::cout << num_1.to_integer() << " + " << num_2.to_integer() << "\n";
	
	
	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_14\\execution_times.txt" };
	auto start = std::chrono::high_resolution_clock::now();
	auto computer = SeaportComputer("../../../../Day_14/input.txt");
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Input read in: " << duration.count() << " microseconds.\n";
	
	start = std::chrono::high_resolution_clock::now();
	uint64_t answer_part_one = computer.part_one();
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Part one calculated in: " << duration.count() << " microseconds.\n";
	
	std::cout << "Part one answer: " << answer_part_one << "\n";
	
	start = std::chrono::high_resolution_clock::now();
	uint64_t answer_part_two = computer.part_two();
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Part two calculated in: " << duration.count() << " microseconds.";
	
	std::cout << "Part two answer: " << answer_part_two << "\n";
   	

}
