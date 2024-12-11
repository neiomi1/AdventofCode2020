#pragma once

#include <string>
#include <set>
#include <queue>
#include <algorithm>
#include <istream>
#include <fstream>
#include <chrono>
#include <iostream>
#include <unordered_map>
#include <regex>

#include <unordered_map>

class Cube_map {
protected:
	struct coordinates_3D
	{
		long x;
		long y;
		long z;

		friend bool operator==(const coordinates_3D& lhs, const coordinates_3D& rhs) {
			return std::tie(lhs.x, lhs.y, lhs.z) == std::tie(rhs.x, rhs.y, rhs.z);
		}

		friend bool operator!=(const coordinates_3D& lhs, const coordinates_3D& rhs) {
			return !(lhs == rhs);
		}


		friend bool operator>(const coordinates_3D& lhs, const coordinates_3D& rhs) {
			return std::tie(lhs.x, lhs.y, lhs.z) > std::tie(rhs.x, rhs.y, rhs.z);
		}

		friend bool operator<(const coordinates_3D& lhs, const coordinates_3D& rhs) {
			return std::tie(lhs.x, lhs.y, lhs.z) < std::tie(rhs.x, rhs.y, rhs.z);
		}

	};

	struct coordinates_4D
	{
		long x;
		long y;
		long z;
		long w;

		friend bool operator==(const coordinates_4D& lhs, const coordinates_4D& rhs) {
			return std::tie(lhs.x, lhs.y, lhs.z,lhs.w) == std::tie(rhs.x, rhs.y, rhs.z,rhs.w);
		}

		friend bool operator!=(const coordinates_4D& lhs, const coordinates_4D& rhs) {
			return !(lhs == rhs);
		}


		friend bool operator>(const coordinates_4D& lhs, const coordinates_4D& rhs) {
			return std::tie(lhs.x, lhs.y, lhs.z,lhs.w) > std::tie(rhs.x, rhs.y, rhs.z,rhs.w);
		}

		friend bool operator<(const coordinates_4D& lhs, const coordinates_4D& rhs) {
			return std::tie(lhs.x, lhs.y, lhs.z,lhs.w) < std::tie(rhs.x, rhs.y, rhs.z,rhs.w);
		}

	};
public:

	Cube_map(const std::string& filepath);

	void read_start();

	void calculate_round_3D();

	void calculate_round_4D();

	uint64_t part_one();

	uint64_t part_two();

private:
	std::set<coordinates_3D> cubes_;
	std::set<coordinates_4D> hypercubes_;
	long round_ = 0;
	std::string filepath_;
};