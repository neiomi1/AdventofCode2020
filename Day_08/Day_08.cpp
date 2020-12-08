

#include "Day_08.h"

#include <fstream>
#include <chrono>
#include <sstream>


GameConsole::GameConsole(const std::string& filepath)
{
	parse_input(filepath);
}

void GameConsole::add_instruction(const std::string& instruction, int argument)
{
	Instruction temp_instruction = Instruction{ instruction, argument, false };
	instructions_.push_back(temp_instruction);
}

void GameConsole::parse_input(const std::string& filepath)
{
	auto file = std::ifstream{ filepath };
	std::string line;
	while (std::getline(file, line)) {
		auto stream = std::istringstream{ line };
		std::string instruction;
		int argument;
		stream >> instruction >> argument;
		add_instruction(instruction, argument);
	}
}

void GameConsole::reset()
{
	for (auto& instruction : instructions_) {
		instruction.visited = false;
	}
	accumulator_ = 0;
	program_counter_ = 0;
}

void GameConsole::execute_instruction()
{
	const std::string instruction = instructions_.at(program_counter_).instruction;
	instructions_.at(program_counter_).visited = true;

	if (instruction == "acc") {
		accumulator_ += instructions_.at(program_counter_).argument;
		program_counter_++;
		return;
	}

	if (instruction == "nop") {
		program_counter_++;
		return;
	}

	if (instruction == "jmp") {
		program_counter_ += instructions_.at(program_counter_).argument;
		return;
	}
}

int GameConsole::run_until_loop()
{
	while (program_counter_ < instructions_.size()) {
		if (instructions_.at(program_counter_).visited == false) {
			execute_instruction();
		}
		else {
			return accumulator_;	
		}
	}
	return accumulator_;
}

bool GameConsole::check_loop()
{
	while (program_counter_ < instructions_.size()) {
		if (instructions_[program_counter_].visited == true) {
			reset();
			return true;
		}
		execute_instruction();
	}
	reset();
	return false;
}

void GameConsole::fix_loop()
{
	for (auto& instruction : instructions_) {
		if (instruction.instruction == "acc") {
			continue;
		}
		if (instruction.instruction == "nop" && instruction.argument != 0) {
			instruction.instruction = "jmp";
			if (!check_loop()) {
				return;
			}
			instruction.instruction = "nop";
			continue;
		}

		if (instruction.instruction == "jmp") {
			instruction.instruction = "nop";
			if (!check_loop()) {
				return;
			}
			instruction.instruction = "jmp";
			continue;
		}
	}
}

int GameConsole::fix_run()
{
	fix_loop();

	while (program_counter_ < instructions_.size()) {
		execute_instruction();
	}

	int result = accumulator_;
	reset();
	return result;
}