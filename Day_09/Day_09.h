#pragma once

#include <string>
#include <set>
#include <queue>
#include <algorithm>

// Using Map Wrapper - keeping at max 25 elements in the map.

template<class T>
class MaxSet {
public:
	MaxSet(int max_size) :max_size_(max_size) {}

	MaxSet(int max_size, const std::vector<T>& input): max_size_(max_size), input_(input){}

	void read_input(const std::string& filepath);

	void insert(T element);

	void clear();

	bool find_pair(T sum_goal)const;

	T bad_insert()const { return first_bad_insert_; }

	T read_until_bad();

	int sum();

	bool read_until(int goal);

	int find_bad_set();

private:
	int max_size_ = 0;
	std::vector<T> input_{};
	std::set<T> content_{};
	std::queue<T> order_{};
	T first_bad_insert_{};
};

