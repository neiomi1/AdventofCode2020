#include "Day_04.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <unordered_map>
#include <sstream>
#include <regex>


Passport::Passport(const std::string& passport) {
	std::string temp;
	auto stream = std::istringstream{ passport };
	byr = 0; 
	iyr = 0; 
	eyr = 0; 
	hgt = 0; 
	pid = 0; 
	cid = 0;
	hcl = ""; 
	ecl = "";
	metric = true;
	valid=true;

	//auto file = std::ofstream{ "..\\..\\..\\..\\Day_04\\output.txt", std::ios::app };
	//file << passport << "\n";

	while (stream >> temp) {
		//std::cout << temp << "\n";
		auto it = temp.find(":");
		std::string lhs = temp.substr(0, it);
		std::string rhs = temp.substr(it+1);
		//std::cout << temp << "  " << lhs << " "<< rhs << "\n";
		if (lhs == "byr") {
			auto reg = std::regex("[0-9][0-9][0-9][0-9]");
			if (std::regex_match(rhs, reg)) {
				byr = std::stoi(rhs);
			}
			//file << "byr " << byr;
			if (!(byr >= 1920 && byr <= 2002)) {
				valid = false;
				//file << " bad byr";
			}
			//file << "\n";
		}
		if (lhs == "iyr") {
			auto reg = std::regex("20[1-2][0-9]");
			if (std::regex_match(rhs, reg)) {
				iyr = std::stoi(rhs);
				//file << "iyr " << iyr;
				if (!(iyr <= 2020 && iyr >= 2010)) {
					valid = false;
					//file << " bad iyr";
				}
			}
			else {
				valid = false;
			}
			//file << "\n";
		}
		if (lhs == "eyr") {
			auto reg = std::regex("20[2-3][0-9]");
			if (std::regex_match(rhs, reg)) {
				eyr = std::stoi(rhs);
				//file << "eyr " << eyr;
				if (!(eyr <= 2030 && eyr >= 2020)) {
					valid = false;
					//file << " bad eyr";
				}
			}
			else {
				valid = false;
			}
			//file << "\n";
		}
		if (lhs == "hgt") {
			auto met_it = rhs.find("cm");
			auto in_it = rhs.find("in");
			if (met_it != std::string::npos) {
				rhs = rhs.substr(0, rhs.size() - 2);
				metric = true;
			}
			else if(in_it!=std::string::npos) {
				rhs = rhs.substr(0, rhs.size() - 2);
				metric = false;
			}
			else {
				valid = false;
			}
			hgt = std::stoi(rhs);
			if (!((metric == true && hgt >= 150 && hgt <= 193 )|| (metric == false && hgt >= 59 && hgt <= 76))) {
				valid = false;
			}
			//file << "hgt " << hgt << "\n";
		}
		if (lhs == "hcl") {
			hcl = rhs;
			auto reg = std::regex("#[0-9a-f][0-9a-f][0-9a-f][0-9a-f][0-9a-f][0-9a-f]");
			if (!std::regex_match(rhs, reg)) {
				valid = false;
			}
			//file << "hcl " << hcl << "\n";
		}
		if (lhs == "ecl") {
			ecl = rhs;
			auto reg = std::regex("amb||blu||brn||gry||grn||hzl||oth");
			if (!std::regex_match(ecl, reg)) {
				valid = false;
			}
			//file << "ecl " << ecl << "\n";
		}
		if (lhs == "pid") {
			auto reg = std::regex("[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]");
			if (std::regex_match(rhs, reg)) {
				pid = std::stoi(rhs);
				//file << "pid " << pid << "\n";
			}
			else {
				valid = false;
			}
		}
	}

	//file << "valid: " << valid<< "\n";
}



void read_entries(const std::string& filename, std::vector<std::string>& passports) {
	auto file = std::ifstream{ "..\\..\\..\\..\\Day_04\\" + filename };
	std::string line;
	std::string passport;
	while (std::getline(file, line)){
		if (line.empty() && !passport.empty()) {
			passports.push_back(passport);
			passport = "";
		}
		if (!line.empty()) {
			passport += line + " ";
		}
	}
	if (!passport.empty()) {
		passports.push_back(passport);
	}
}

bool validate_passport_lenient(const std::string& passport) {
	//auto file = std::ofstream{ "..\\..\\..\\..\\Day_04\\output.txt" };
	//file << passport << "\n";
	std::string field[7] = {"byr","iyr", "eyr", "hgt", "hcl", "ecl","pid"};
	for (int i = 0; i < 7; i++) {
		if (passport.find(field[i]) != std::string::npos) {
			//file << "found: " + field[i] << "\n";
			continue;
		}
		else {
			return false;
		}
	}
	return true;
}

int count_lenient_passports(std::vector<std::string>& passports, std::vector<std::string>& lenient_passports) {
	int valid = 0;
	for (const auto& passport : passports) {
		if (validate_passport_lenient(passport)) {
			lenient_passports.push_back(passport);
			valid++;
		}
	}
	return valid;
}

int count_rigid_passports(std::vector<std::string>& lenient_passports) {
	int valid = 0;
	for (const auto& passport : lenient_passports) {
		if (Passport(passport).valid) {
			valid++;
		}
	}
	return valid;

}


int main()
{
	auto passports = std::vector<std::string>{};

	auto lenient_passports = std::vector<std::string>{};

	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_04\\execution_times.txt" };
	auto start = std::chrono::high_resolution_clock::now();
	read_entries("input.txt", passports);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Input read in " << duration.count() << " microseconds.\n";
	
	start = std::chrono::high_resolution_clock::now();
	int valid_passports = count_lenient_passports(passports,lenient_passports);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Number of lenient passports found in: " << duration.count() << " microseconds.\n";
	
	std::cout <<"Number of lenient passports : "<< valid_passports << "\n";
	
	start = std::chrono::high_resolution_clock::now();
	valid_passports = count_rigid_passports(lenient_passports);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Number of rigid passports found in: " << duration.count() << " microseconds.";
	
	std::cout << "Number of rigid passports: " << valid_passports << "\n";

}
