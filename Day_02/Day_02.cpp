// AdventofCodeDay1.cpp : Defines the entry point for the application.
//

#include "Day_02.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono>


void read_entries(const std::string& filename, std::vector<Password>& passwords) {
	auto file = std::ifstream{ "..\\..\\..\\..\\Day_02\\" + filename };
	Password temp_password{};
	while (file >> temp_password) {
		passwords.push_back(temp_password);
	}
}
//old policy - part 1
int count_valid_passwords_old_policy(const std::vector<Password>& passwords) {
	int num_good_password = 0;
	for (const auto& p : passwords) {
		auto occurences = std::count(p.password.begin(), p.password.end(), p.c);
		if (occurences >= p.min && occurences <= p.max) {
			num_good_password++;
		}
	}
	return num_good_password;
}

//new policy - part 2
int count_valid_passwords_new_policy(const std::vector<Password>& passwords) {
	int num_good_password = 0;
	for (const auto& p : passwords) {
		if ((p.password[p.min - 1] == p.c) ^ (p.password[p.max - 1] == p.c)) {
			num_good_password++;
		}
	}
	return num_good_password;
}


int main()
{
	std::vector<Password> passwords = {};

	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_02\\execution_times.txt" };
	auto start = std::chrono::high_resolution_clock::now();
	read_entries("input.txt", passwords);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Input read in " << duration.count() << " microseconds.\n";

	start = std::chrono::high_resolution_clock::now();
	int good_passwords = count_valid_passwords_old_policy(passwords);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Bad passwords calculated in " << duration.count() << " microseconds.\n";

	std::cout << "Number of good passwords: " << good_passwords << "\n";

	start = std::chrono::high_resolution_clock::now();
	good_passwords = count_valid_passwords_new_policy(passwords);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Triple calculated in " << duration.count() << " microseconds.";

	std::cout << "Number of good passwords (new policy): " << good_passwords << "\n";

}
