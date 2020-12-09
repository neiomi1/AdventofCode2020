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

// Using Map Wrapper - keeping at max 25 elements in the map.

template<class T>
class MaxSet {
public:
	MaxSet(int max_size) :max_size_(max_size) {}

	MaxSet(int max_size, const std::vector<T>& input): max_size_(max_size), input_(input){}

	void read_input(const std::string& filepath) {
		auto file = std::ifstream{ filepath };
		T element;
		while (file >> element) {
			input_.push_back(element);
		}
	}


	void insert(T element) {
		if (std::ssize(content_) < max_size_) {
			content_.insert(element);
			order_.push(element);
		}
		else {
			content_.erase(order_.front());
			order_.pop();

			content_.insert(element);
			order_.push(element);
		}
	}

	void clear() {
		content_.clear();
		while (order_.size() > 0) {
			order_.pop();
		}
	}


	bool find_pair(T sum_goal)const {
		for (auto i = content_.begin(); i != content_.end(); i++) {
			for (auto j = i; j != content_.end(); j++) {
				int temp_sum = *i + *j;
				if (temp_sum > sum_goal) {
					break;
				}
				if (temp_sum == sum_goal) {
					return true;
				}
			}
			if (*i > sum_goal) {
				break;
			}
		}
		return false;
	}


	T bad_insert()const { return first_bad_insert_; }

	T read_until_bad() {
		for (auto element : input_) {
			if (content_.size() < max_size_) {
				insert(element);
			}
			else if (find_pair(element)) {
				insert(element);
			}
			else {
				return element;
			}
		}
		return bad_insert();
	}


	int sum() {
		return std::accumulate(content_.begin(), content_.end(), 0);
	}

	bool read_until(int goal) {
		for (auto element : input_) {
			insert(element);
			if (order_.front() > goal) {
				return false;
			}
			if (sum() == goal) {
				first_bad_insert_ = *content_.begin() + *content_.rbegin();
				return true;
			}
		}
		return false;
	}

	int find_bad_set() {
		clear();
		T goal = read_until_bad();
		for (int i = 2; i < goal; i++) {
			auto set = MaxSet<T>(i, input_);
			if (set.read_until(goal)) {
				return set.bad_insert();
			}
			std::cout << "testing: " << i << "\n";
		}
		return -1;
	}


private:
	int max_size_ = 0;
	std::vector<T> input_{};
	std::set<T> content_{};
	std::queue<T> order_{};
	T first_bad_insert_{};
};

