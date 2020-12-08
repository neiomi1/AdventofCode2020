// AdventofCodeDay1.cpp : Defines the entry point for the application.
//

#include "Day_05.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <string>
#include <chrono>
#include <bitset>

void Seat::calculate_seatID() {
	for (auto it = partitioning_.begin(); it != partitioning_.end(); it++) {
		switch (*it) {
		case 'B': *it = '1'; break;
		case 'F': *it = '0'; break;
		case 'L': *it = '0'; break;
		case 'R': *it = '1'; break;
		}
	}

	auto row = partitioning_.substr(0, 7);
	auto col = partitioning_.substr(7, 10);

	seatID_ = std::stoi(row, 0, 2) * 8 + std::stoi(col, 0, 2);
}

int find_highest_seatID(std::vector<Seat>& seats) {
	for (auto& seat : seats) {
		seat.calculate_seatID();
	}
	std::sort(seats.begin(), seats.end(), std::greater());
	return seats[0].seatID();
}

void read_lines(const std::string& filename, std::vector<Seat>& seats) {
	auto file = std::ifstream{ "../../../../Day_05/" + filename };
	std::string line;
	while (file >> line) {
		auto temp = Seat(line);
		seats.push_back(temp);
	}
}

void print_seats(const std::string& filename, const std::vector<Seat>& seats) {
	auto file_out = std::ofstream{ "../../../../Day_05/" +filename};
	std::for_each(seats.begin(), seats.end(), [&](const auto& seat) {file_out << seat.seatID() << "\n"; });
}

int find_empty_seat(const std::vector<Seat>& seats) {
	auto seat = seats[0].seatID()-1;

	for (int i = 1; i < seats.size(); i++) {
		if (seat != seats[i].seatID()) {
			return seat;
		}
		seat--;
	}
	return -1;
}

int main()
{
	std::vector<Seat> seats;
	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_05\\execution_times.txt" };

	auto start = std::chrono::high_resolution_clock::now();
	read_lines("input.txt", seats);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Input read in " << duration.count() << " microseconds.\n";


	start = std::chrono::high_resolution_clock::now();
	int seatID = find_highest_seatID(seats);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Part one done in: " << duration.count() << " microseconds.\n";

	std::cout << "Highest Seat ID: " << seatID << "\n";
	
	start = std::chrono::high_resolution_clock::now();
	seatID = find_empty_seat(seats);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Part two done in: " << duration.count() << " microseconds.\n";

	std::cout << "Empty Seat ID: " << seatID << "\n";

}
