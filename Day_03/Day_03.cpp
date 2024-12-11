

#include "Day_03.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <unordered_map>



void read_entries(const std::string& filename, Tree_Biome& biome){
	auto file = std::ifstream{ "..\\..\\..\\..\\Day_03\\" + filename };
	std::string line;
	int line_num = 0;
	while (file >> line) {
		biome.repeating_pattern[line_num] = (int)std::ssize(line);
		for (int i = 0; i < std::ssize(line); i++) {
			if (line[i] == '#') {
				biome.tree_map[line_num][i] = true;
			}
		}
		line_num++;
	}
	biome.size = line_num;
}



int count_trees_on_path(const Tree_Biome& trees, int x_diff, int y_diff) {
	int encountered_trees = 0;
	int x = 0;
	int y = 0;
	while (y+y_diff < trees.size) {
		y += y_diff;
		x += x_diff;
		x %= trees.repeating_pattern.at(y);
		if (trees.tree_map.at(y).find(x) != trees.tree_map.at(y).end()) {
			encountered_trees++;
		}
	}
	return encountered_trees;
}


int count_multiple_paths(const Tree_Biome& trees) {
	const auto paths = std::vector<std::pair<int, int>>{ {1,1},{3,1},{5,1},{7,1},{1,2}};
	int tree_num = 1;
	for (const auto& path : paths) {
		tree_num *= count_trees_on_path(trees, path.first, path.second);
	}
	return tree_num;
}

int main()
{
	auto trees = Tree_Biome{};

	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_03\\execution_times.txt" };
	auto start = std::chrono::high_resolution_clock::now();
	read_entries("input.txt", trees);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Input read in " << duration.count() << " microseconds.\n";

	start = std::chrono::high_resolution_clock::now();
	int num_trees = count_trees_on_path(trees, 3, 1);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Number of trees found in: " << duration.count() << " microseconds.\n";

	std::cout << "Number of trees on the path: " << num_trees << "\n";

	start = std::chrono::high_resolution_clock::now();
	num_trees = count_multiple_paths(trees);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "All paths calculated in: " << duration.count() << " microseconds.";

	std::cout << "Number of trees on given paths: " << num_trees << "\n";

}
