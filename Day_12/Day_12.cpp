#include "Day_12.h"

Ferry::Ferry(const std::string& filepath):filepath_(filepath)
{
	read_input(filepath_);
}

void Ferry::read_input(const std::string& filepath)
{
	auto file = std::ifstream{ filepath };
	while (!file.eof()) {
		Instruction instruction;
		file >> instruction.id >> instruction.amount;
		instructions_.push_back(instruction);
	}
	std::cout << "parsed instructions:" << instructions_.size() << "\n";
}

void Ferry::execute(const Instruction& instruction, bool enable_waypoint)
{
	switch (instruction.id) {
	case 'F':
		if (enable_waypoint) {
			x_ += waypoint_.first * instruction.amount;
			y_ += waypoint_.second * instruction.amount;
		}
		else {
			x_ += dirs[dir].first * instruction.amount;
			y_ += dirs[dir].second * instruction.amount;
		}
		return;
	case 'N':
		if (enable_waypoint) {
			waypoint_.second += instruction.amount;
		}
		else {
			y_ += instruction.amount;
		}
		return;
	case 'E':
		if (enable_waypoint) {
			waypoint_.first += instruction.amount;
		}
		else {
			x_ += instruction.amount;
		}
		return;
	case 'S':
		if (enable_waypoint) {
			waypoint_.second -= instruction.amount;
		}
		else {
			y_ -= instruction.amount;
		}
		return;
	case 'W':
		if (enable_waypoint) {
			waypoint_.first -= instruction.amount;
		}
		else {
			x_ -= instruction.amount;
		}
		return;
	case 'L':
		if (enable_waypoint) {
			int turn = (instruction.amount / 90) % 4;
			for (int n = 0; n < turn; n++) {
				int temp = waypoint_.second * -1;
				waypoint_.second = waypoint_.first;
				waypoint_.first = temp;
			}
		}
		else {
			//std::cout << "L: " << dir << " - " << instruction.amount;
			dir -= (instruction.amount / 90) % 4;
			//std::cout << " " << dir;
			dir = dir < 0 ? 4 + dir : dir;
			//std::cout << " -> " << dir << "\n";
		}
		return;
	case 'R':
		if (enable_waypoint) {
			int turn = (instruction.amount / 90) % 4;
			for (int n = 0; n < turn; n++) {
				int temp = waypoint_.first * -1;
				waypoint_.first = waypoint_.second;
				waypoint_.second = temp;
			}
		}
		else {
			//std::cout << "R: " << dir << " + " << instruction.amount;
			dir += (instruction.amount / 90) % 4;
			dir %= 4;
			//std::cout << " -> " << dir << "\n";
		}
		return;
	}
}

void Ferry::reset()
{
	x_ = 0;
	y_ = 0;
	waypoint_ = { 10,1 };
	dir = 1;
}

int Ferry::part_one() {
	reset();
	for (const auto& Instruction : instructions_) {
		execute(Instruction);
	}
	return abs(x_) + abs(y_);
}

int Ferry::part_two() {
	reset();
	for (const auto& Instruction : instructions_) {
		execute(Instruction, true);
	}
	return abs(x_) + abs(y_);
}