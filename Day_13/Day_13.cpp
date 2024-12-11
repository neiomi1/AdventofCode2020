#include "Day_13.h"
#include <regex>

void BusHub::read_entries(const std::string& filepath)
{
	auto file = std::ifstream{ filepath };
	file >> starting_point_;
	std::string line;
	std::regex match_number = std::regex("([0-9]+|x)");
	file >> line;
	std::sregex_iterator numbers(line.begin(), line.end(), match_number), end_numbers;
	for (; numbers != end_numbers; numbers++) {
		//std::cout << (*numbers)[0] << "\n";
		if ((*numbers)[0] == "x") {
			bus_IDs_.push_back(0);
		}
		else {
			bus_IDs_.push_back(std::stoi((*numbers)[0]));
		}
	}
	//std::cout << starting_point_ << " " << bus_IDs_.size() << "\n";
}

int BusHub::calculate_wait(int bus_ID)
{
	return bus_ID - (starting_point_ % bus_ID);
}

int BusHub::part_one()
{
	int waiting_time = starting_point_;
	int id = 0;
	for (const auto& bus_ID : bus_IDs_) {
		if (bus_ID == 0) {
			continue;
		}
		int temp = calculate_wait(bus_ID);
		if (waiting_time > temp) {
			waiting_time = temp;
			id = bus_ID;
		}
	}
	return id * waiting_time;
}

// Chinese Remainder Theorem
uint64_t BusHub::part_two()
{
	int minute = -1;
	uint64_t mult = 0;
	for (const auto& bus_ID : bus_IDs_) {
		minute++;
		if (bus_ID == 0) {
			continue;
		}
		if (minute == 0) {
			mult = (uint64_t)bus_ID;
		}
		else {
			//std::cout << bus_ID << ": " << bus_ID - (minute % bus_ID) << "\n";
			wait_time_[bus_ID] = bus_ID - (minute % bus_ID);
		}
	}
	uint64_t timestamp = 0;
	
	for (auto it = wait_time_.begin(); it != wait_time_.end(); it++) {
		//std::cout << (*it).first << " " << (*it).second << " \n";
		while ((timestamp % (*it).first) != (*it).second) {
			timestamp += mult;
		}
		mult *= (*it).first;
		//std::cout << timestamp << "\n";
	}
	return timestamp;
}
