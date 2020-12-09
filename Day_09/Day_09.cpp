#include <istream>
#include <fstream>
#include <chrono>
#include <sstream>
#include <iostream>
#include <numeric>

#include "Day_09.h"

template<class T>
void MaxSet<T>::read_input(const std::string& filepath)
{
	auto file = std::ifstream{ filepath };
	T element;
	while (file >> element) {
		input_.push_back(element);
	}
}

template<class T>
inline void MaxSet<T>::insert(T element)
{
	if (std::ssize(content_) < max_size_) {
		content_.insert(element);
		order_.push(element);
	}
	else{
		content_.erase(order_.front());
		order_.pop();

		content_.insert(element);
		order_.push(element);
	}
}

template<class T>
void MaxSet<T>::clear()
{
	content_.clear();
	while (order_.size() > 0) {
		order_.pop();
	}
}

template<class T>
inline bool MaxSet<T>::find_pair(T sum_goal)const
{
	for (auto i = content_.begin(); i != content_.end();i++) {
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

template<class T>
inline T MaxSet<T>::read_until_bad()
{
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

template<class T>
int MaxSet<T>::sum()
{
	return std::accumulate(content_.begin(), content_.end(), 0);
}

template<class T>
bool MaxSet<T>::read_until(int goal)
{
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



template<class T>
int MaxSet<T>::find_bad_set()
{
	clear();
	T goal = read_until_bad();
	for (int i = 2;i < goal; i++) {
		auto set = MaxSet<T>(i, input_);
		if (set.read_until(goal)) {
			return set.bad_insert();
		}
		std::cout << "testing: " << i << "\n";
	}
	return -1;
}
