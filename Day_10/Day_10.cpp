#include "Day_10.h"

Adapters::Adapters(const std::string& filepath)
{
	auto file = std::ifstream{ filepath };
	int temp;
	while (file >> temp) {
		jolts_.push_back(temp);
	}
	std::sort(jolts_.begin(), jolts_.end());
}

int Adapters::part_one()
{
	int diff_3 = 1; //device starts at max + 3
	int diff_2 = 0;
	int diff_1 = 0;
	auto temp = std::vector<int>{};
	for (int n = 0; n < std::ssize(jolts_) - 1; n++) {
		switch (jolts_[n + 1] - jolts_[n]) {
		case 1: diff_1++; temp.push_back(n); break;
		case 2: diff_2++; break;
		case 3: diff_3++; temp.push_back(n); jolt_groups_.push_back(temp); temp = std::vector<int>{}; break;
		}
	}
	temp.push_back((int)std::ssize(jolts_) - 1);
	jolt_groups_.push_back(temp);

	std::cout << "1 jolt difference " << diff_1 << "\n2 jolt difference " << diff_2 << "\n3 jolt difference " << diff_3 << "\n";
	return diff_1 * diff_3;
}

//Tribonacci numbers. Though I did those by hand and realized the pattern after :(
uint64_t Adapters::calculate_permutations(int size)
{
	if (memory_.contains(size)) {
		return memory_[size];
	}
	else {
		uint64_t temp = calculate_permutations(size - 1) + calculate_permutations(size - 2) + calculate_permutations(size - 3);
		memory_[size] = temp;
		return temp;
	}
}

uint64_t Adapters::part_two()
{
	//if you like further output just uncomment
	auto file = std::ofstream{ "../../../../Day_10/output.txt" };
	uint64_t result = 1;
	for (const auto& jolt_group : jolt_groups_) {

		file << "[ " << result << " " << calculate_permutations((int)std::ssize(jolt_group));
		result *= calculate_permutations((int)std::ssize(jolt_group));
		//for (const auto& num : jolt_group) {
		//	file << jolts_[num] << " ";
		//}
		file << " " << result << "]\n";
	}
	return result;
}
