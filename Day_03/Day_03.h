// AdventofCodeDay1.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <istream>
#include<fstream>
#include<unordered_map>

// TODO: Reference additional headers your program requires here.

struct Tree_Biome {
	int size;
	std::unordered_map<int, std::unordered_map<int, bool>> tree_map;
	std::unordered_map<int, int> repeating_pattern;
};