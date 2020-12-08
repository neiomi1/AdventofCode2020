// AdventofCodeDay1.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include<fstream>
#include <vector>

// Doing OOP in case this gets intcode level messy


struct Instruction {
	std::string instruction;
	const int argument;
	bool visited;
};

using instructions = std::vector<Instruction>;

class GameConsole {
public:
	GameConsole(const instructions& instructions) : instructions_(instructions) {};

	GameConsole(const std::string& filepath);

	void add_instruction(const std::string& instruction, int argument);

	void parse_input(const std::string& filepath);

	void reset();

	void execute_instruction();
	
	int run_until_loop();

	bool check_loop();

	void fix_loop();

	int fix_run();

private:
	instructions instructions_;
	int program_counter_ = 0;
	int accumulator_ = 0;
};