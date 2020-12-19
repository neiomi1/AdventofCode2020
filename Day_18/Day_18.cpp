#include <sstream>
#include "Day_18.h"

Calculator::Calculator(const std::string& input):input_(input)
{
}

uint64_t Calculator::calculate(int pos)
{
	uint64_t result = 0;
	bool num = false;
	for (int i = pos; i < std::ssize(input_); i++) {
		if (input_[i] >= '0' && input_[i] <= '9') {
			if (!num) {
				result = input_[i] - '0';
			}
		}
	}
	return 0;
}
