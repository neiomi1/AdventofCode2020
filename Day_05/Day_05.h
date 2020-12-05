// AdventofCodeDay1.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>

// TODO: Reference additional headers your program requires here.


class Seat {
public:
	Seat(const std::string& partition) {
		partitioning_ = partition;
	}

	const std::string& partitioning() const { return partitioning_; }

	void calculate_seatID();

	int seatID() const { return seatID_; }


	bool operator>(const Seat& seat) const {
		return seatID_ > seat.seatID_;
	}
	bool operator<(const Seat& seat) const {
		return seatID_ < seat.seatID_;
	}
	bool operator==(const Seat& seat) const {
		return seatID_ == seat.seatID_;
	}
	bool operator>=(const Seat& seat) const {
		return seatID_ >= seat.seatID_;
	}
	bool operator<=(const Seat& seat) const {
		return seatID_ <= seat.seatID_;
	}

private:
	std::string partitioning_;
	int seatID_ = 0;
};