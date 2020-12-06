// AdventofCodeDay1.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include<fstream>
#include<unordered_map>

// TODO: Reference additional headers your program requires here.


struct DeclarationForm {
	std::unordered_map<char, int> answers;
	int number_of_people = 1;
};