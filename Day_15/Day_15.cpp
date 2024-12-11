#include "Day_15.h"

Memory_game::Memory_game(const std::string& filepath) : filepath_(filepath) {}

void Memory_game::reset()
{
	round_ = 0;
	memory_.clear();
}


void Memory_game::read_start()
{
	auto file = std::ifstream{ filepath_ };
	int n;
	char c;
	while (file >> n) {
		round_++;
		//std::cout << n << "\n";
		memory_[n] = round_;
		last_number_ = n;
		file >> c;
	}
}

void Memory_game::simulate_round()
{
	round_++;
	int last = memory_[last_number_];
	memory_[last_number_] = round_ - 1;
	if (last == 0) {
		last_number_ = 0;
	}
	else {
		last_number_ = round_ - 1 - last;
	}
}

int Memory_game::part_one(int target)
{
	reset();
	memory_.resize(target);
	read_start();
	while (round_ < target) {
		simulate_round();
	}
	return last_number_;
}

