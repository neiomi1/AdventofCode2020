#pragma once
#include <string>
#include <set>
#include <queue>
#include <algorithm>
#include <istream>
#include <fstream>
#include <chrono>
#include <sstream>
#include <iostream>
#include <numeric>
#include <unordered_map>

class BitInteger {
public:
	BitInteger(const std::string& content, int system);

	BitInteger(int size = 36);

	void set(const std::string& value);

	uint64_t to_integer() const;

	void print() const;

	void mask(const BitInteger& mask);

	void mask_v2(const BitInteger& mask);

	std::vector<BitInteger> resolve_address();

	BitInteger& operator+= (const BitInteger& num);



private:
	std::vector<BitInteger> recursive_resolve(std::string bits, int pos) {
		auto result = std::vector<BitInteger>{};
		for (int n = pos; n < bits.size(); n++) {
			if (bits[n] == 'X') {
				bits[n] = '0';
				auto temp = recursive_resolve(bits, n);
				for (auto& elem : temp) {
					result.push_back(elem);
				}
				bits[n] = '1';
				temp = recursive_resolve(bits, n);
				for (auto& elem : temp) {
					result.push_back(elem);
				}
				return result;
			}
		}
		result.push_back(BitInteger(bits, 2));
		return result;
	}

	std::string bits_;
	int size_ = 36;
};

class SeaportComputer {
public:
	SeaportComputer(const std::string& filepath);

	void reset();

	void execute(const std::string&, bool version = false);

	uint64_t part_one();

	uint64_t part_two();

private:
	std::unordered_map<uint64_t, BitInteger> addresses_;
	BitInteger mask_;
	std::string filepath_;
};