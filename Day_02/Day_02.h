// AdventofCodeDay1.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <istream>
#include<fstream>

// TODO: Reference additional headers your program requires here.

struct Password {
	//policy:
	int min, max;
	char c;
	//used password
	std::string password;

	friend std::istream& operator>>(std::istream& in, Password &password);
	
	
	void print() {
		auto file_out = std::ofstream{ "..\\..\\..\\..\\Day_02\\read_input.txt" , std::ios::app};
		file_out << min << "-" << max << " " << c << ": " << password << "\n";
	}

};

std::istream& operator>>(std::istream& in, Password &password) {
	char temp;
	in >> password.min;
	in >> temp;
	in >> password.max;
	in >> password.c;
	in >> temp;
	in >> password.password;
	return in;
}