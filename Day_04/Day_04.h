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


struct Passport {
	int byr, iyr, eyr, hgt, pid, cid;
	std::string hcl, ecl;
	bool metric, valid;

	Passport(const std::string& passport);


};