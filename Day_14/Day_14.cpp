#include "Day_14.h"
#include <regex>

BitInteger::BitInteger(const std::string& content, int system)
{
	if (system == 2) {
		bits_ = content;
		size_ = (int)std::ssize(content);
	}
	if (system == 10) {
		bits_ = "";
		uint64_t temp = static_cast<uint64_t>(std::stoi(content));
		for (int n = 35; n >= 0; n--) {
			uint64_t exp = static_cast<uint64_t>(pow(2, n));
			//std::cout << temp << " " << exp << " " << temp / exp  << "\n";
			if (temp / exp >  0) {
				temp %= exp;
				bits_ += "1";
			}
			else {
				bits_ += "0";
			}
		}
		size_ = (int)std::ssize(bits_);
	}
}

BitInteger::BitInteger(int size) : size_(size)
{
	for (int n = 0; n < size_; n++) {
		bits_ += "0";
	}
}


void BitInteger::set(const std::string& value)
{
	bits_ = value;
	size_ = (int)std::ssize(bits_);
}

uint64_t BitInteger::to_integer() const
{
	uint64_t result = 0;
	for (int n = size_-1; n >= 0; n--) {
		if (bits_[n] == '1') {
			uint64_t upow = 1;
			for (int i = size_ -1; i > n; i--) {
				upow *= 2;
			}
			result += upow;
		}
	}
	return result;
}

void BitInteger::print() const
{
	std::cout << "num bits: " << size_ << " :" << bits_ << "\n";
}

void BitInteger::mask(const BitInteger& mask)
{
	for (int n = size_ - 1; n >= 0; n--) {
		if (mask.bits_[n] == 'X') {
			continue;
		}
		bits_[n] = mask.bits_[n];
	}

}

void BitInteger::mask_v2(const BitInteger& mask)
{
	for (int n = size_ - 1; n >= 0; n--) {
		if (mask.bits_[n] == 'X') {
			bits_[n] = 'X';
		}
		if (mask.bits_[n] == '1') {
			bits_[n] = '1';
		}
	}
}

std::vector<BitInteger> BitInteger::resolve_address()
{
	return recursive_resolve(bits_, 0);
}

BitInteger& BitInteger::operator+=(const BitInteger& num)
{
		char overflow = '0';
		for (int n = num.size_-1; n >= 0; n--) {
			switch (bits_[n]) {
			case '0':
				if (overflow == '1') {
					if (num.bits_[n] == '1') {
						break;
					}
					else {
						bits_[n] = overflow;
						overflow = '0';
						break;
					}
				}
				else {
					bits_[n] = num.bits_[n];
					break;
				}

			case '1':
				if (num.bits_[n] == '1') {
					bits_[n] = overflow;
					overflow = '1';
					break;
				}
				else if (overflow == '0') {
					break;
					}
				else{
				bits_[n] = '0';
				break;
				}
			}
		}
	if (overflow == '1') {
		throw std::out_of_range("Overflow");
	}
	return *this;
}

SeaportComputer::SeaportComputer(const std::string& filepath) : filepath_(filepath)
{
}

void SeaportComputer::reset()
{
	addresses_.clear();
	mask_ = BitInteger();
}

void SeaportComputer::execute(const std::string& command, bool version)
{
	auto pos = command.find("mask = ");
	if (pos != std::string::npos) {
		auto substr = command.substr(7, command.size());
		mask_.set(substr);
	}
	else {
		pos = command.find("=");
		auto lhs = command.substr(4, pos-6);
		auto rhs = command.substr(pos + 2, command.size());
		
		//std::cout << "mem[" << lhs << "] = " << rhs << "\n";
		auto temp = BitInteger(rhs, 10);
		if (!version) {
			temp.mask(mask_);
			addresses_[std::stoi(lhs)] = temp;
		}
		else {
			auto address = BitInteger(lhs, 10);
			address.mask_v2(mask_);
			for (auto& elem : address.resolve_address()) {
				addresses_[elem.to_integer()] = temp;
			}
		}
	}

}

uint64_t SeaportComputer::part_one()
{
	auto file = std::ifstream{ filepath_ };
	std::string line;
	while (std::getline(file, line)) {
		execute(line);
	}
	uint64_t result = 0;
	for (const auto& [address, value] : addresses_) {
		result += value.to_integer();
	}
	return result;
}

uint64_t SeaportComputer::part_two()
{
	reset();
	auto file = std::ifstream{ filepath_ };
	std::string line;
	while (std::getline(file, line)) {
		execute(line, true);
	}
	uint64_t result = 0;
	for (const auto& [address, value] : addresses_) {
		//std::cout << address << " : " << value.to_integer() << "\n";
		result += value.to_integer();
	}
	return result;
	
}
