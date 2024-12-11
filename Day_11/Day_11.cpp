#include "Day_11.h"

Ferry::Ferry(const std::string& filepath):filepath_(filepath)
{
	read_input(filepath_);
}

void Ferry::read_input(const std::string& filepath)
{
	height_ = 0;
	width_ = 0;
	current_seat_map_.clear();
	auto file = std::ifstream{ filepath };
	std::string line;
	while (std::getline(file, line)) {
		auto stream = std::istringstream{ line };
		char c;
		std::vector<int> temp{};
		while (stream >> c) {
			switch (c) {
			case '.': temp.push_back(0); break;
			case 'L': temp.push_back(1); break;
			case '#': temp.push_back(2); break;
			}
		}
		current_seat_map_.push_back(temp);
		height_++;
	}
	width_ = (int)std::ssize(line);
	std::cout << "parsed height:" << current_seat_map_.size() << " parsed width: " << current_seat_map_[0].size() << "\n";
}

int Ferry::check_seat_simple(int x, int y) {
	//auto file = std::ofstream{ "../../../../Day_11/log.txt" , std::ios::app };
	int num_seats = 0;
	int sum = 0;
	if (current_seat_map_[y][x]) {
		if (x > 0) {
			if (current_seat_map_[y][x - 1]) {
				sum += current_seat_map_[y][x - 1];
				num_seats++;
			}
			if (y > 0) {
				if (current_seat_map_[y - 1][x - 1]) {
					sum += current_seat_map_[y - 1][x - 1];
					num_seats++;
				}
				if (current_seat_map_[y - 1][x]) {
					sum += current_seat_map_[y - 1][x];
					num_seats++;
				}
				if (x < width_ - 1 && current_seat_map_[y - 1][x + 1]) {
					sum += current_seat_map_[y - 1][x + 1];
					num_seats++;
				}
			}
			if (y < height_ - 1) {
				if (current_seat_map_[y + 1][x - 1]) {
					sum += current_seat_map_[y + 1][x - 1];
					num_seats++;
				}
				if (current_seat_map_[y + 1][x]) {
					sum += current_seat_map_[y + 1][x];
					num_seats++;
				}

				if (x < width_ - 1 && current_seat_map_[y + 1][x + 1]) {
					sum += current_seat_map_[y + 1][x + 1];
					num_seats++;
				}
			}
			if (x < width_ - 1 && current_seat_map_[y][x + 1]) {
				sum += current_seat_map_[y][x + 1];
				num_seats++;
			}
		}
		else {
			//x == 0
			if (current_seat_map_[y][x + 1]) {
				sum += current_seat_map_[y][x + 1];
				num_seats++;
			}
			if (y > 0) {
				if (current_seat_map_[y - 1][x + 1]) {
					sum += current_seat_map_[y - 1][x + 1];
					num_seats++;
				}
				if (current_seat_map_[y - 1][x]) {
					sum += current_seat_map_[y - 1][x];
					num_seats++;
				}
			}
			if (y < height_ - 1) {
				if (current_seat_map_[y + 1][x + 1]) {
					sum += current_seat_map_[y + 1][x + 1];
					num_seats++;
				}
				if (current_seat_map_[y + 1][x]) {
					sum += current_seat_map_[y + 1][x];
					num_seats++;
				}

			}
		}
		//file << "checking" << x << " " << y;
		if (current_seat_map_[y][x] == 1 && num_seats >= sum) {
			//file << " occupied " << num_seats << " " << sum << " \n";
			return 2;
		}
		else if (current_seat_map_[y][x] == 2 && 3 < sum - num_seats) {
			//file << "free " << num_seats << " " << sum << " \n";
			return 1;
		}
		//file << "same " << num_seats << " " << sum << " \n";
		return current_seat_map_[y][x];
	}
	return 0;
}

int Ferry::check_seat(int x, int y)
{
	if (current_seat_map_[y][x]) {
		bool checked[] = { false,false,false,false,false,false,false,false };
		int temp_x = 0;
		int temp_y = 0;
		int occupied = 0;
		for (int diff = 1; diff < std::max(height_, width_); diff++) {
			// diagonal up left
			if (checked[0] == false) {
				temp_x = x - diff;
				temp_y = y - diff;
				if (temp_x >= 0 && temp_y >= 0) {
					if (current_seat_map_[temp_y][temp_x]) {
						checked[0] = true;
						//std::cout << "current_seat_map_[" << temp_y << "][" << temp_x << "] " << current_seat_map_[temp_y][temp_x] << "\n";
						if (current_seat_map_[temp_y][temp_x] == 2) {
							occupied++;
						}
					}
				}
				else {
					checked[0] = true;
					//std::cout << "up left out of range\n";
				}
				
			}
			//straight up
			if (checked[1] == false) {
				temp_y = y - diff;
				if (temp_y >= 0) {
					if (current_seat_map_[temp_y][x]) {
						checked[1] = true;
						//std::cout << "current_seat_map_[" << temp_y << "][" << x << "] " << current_seat_map_[temp_y][x] << "\n";
						if (current_seat_map_[temp_y][x] == 2) {
							occupied++;
						}
					}
				}
				else { checked[1] = true;
				//std::cout << "up out of range\n";
				}
			}
			//diagonal up right
			if (checked[2] == false) {
				temp_x = x + diff;
				temp_y = y - diff;
				if (temp_y >= 0 && temp_x < width_) {
					if (current_seat_map_[temp_y][temp_x]) {
						checked[2] = true;
						//std::cout << "current_seat_map_[" << temp_y << "][" << temp_x << "] " << current_seat_map_[temp_y][temp_x] << "\n";
						if (current_seat_map_[temp_y][temp_x] == 2) {
							occupied++;
						}
					}
				}
				else { checked[2] = true; 
				//std::cout << "up right out of range\n";
				}
			}
			//straight right
			if (checked[3] == false) {
				temp_x = x + diff;
				if (temp_x < width_) {
					if (current_seat_map_[y][temp_x]) {
						checked[3] = true;
						//std::cout << "current_seat_map_[" << y << "][" << temp_x << "] " << current_seat_map_[y][temp_x] << "\n";
						if (current_seat_map_[y][temp_x] == 2) {
							occupied++;
						}
					}
				}
				else { checked[3] = true; 
				//std::cout << "right out of range\n";
				}
			}
			//diagonal down right
			if (checked[4] == false) {
				temp_x = x + diff;
				temp_y = y + diff;
				if (temp_y < height_ && temp_x < width_) {
					if (current_seat_map_[temp_y][temp_x]) {
						//std::cout << "current_seat_map_[" << temp_y << "][" << temp_x << "] " << current_seat_map_[temp_y][temp_x] << "\n";
						checked[4] = true;
						if (current_seat_map_[temp_y][temp_x] == 2) {
							occupied++;
						}
					}
				}
				else { checked[4] = true;
				//std::cout << "down right out of range\n";
				}
			}
			//down
			if (checked[5] == false) {
				temp_y = y + diff;
				if (temp_y < height_) {
					if (current_seat_map_[temp_y][x]) {
						//std::cout << "current_seat_map_[" << temp_y << "][" << x << "] " << current_seat_map_[temp_y][x] << "\n";
						checked[5] = true;
						if (current_seat_map_[temp_y][x] == 2) {
							occupied++;
						}
					}
				}
				else { checked[5] = true;
				//std::cout << "down out of range\n";
				}
			}
			//diagonal down left
			if (checked[6] == false) {
				temp_x = x - diff;
				temp_y = y + diff;
				if (temp_y < height_ && temp_x >= 0) {
					if (current_seat_map_[temp_y][temp_x]) {
						//std::cout << "current_seat_map_[" << temp_y << "][" << temp_x << "] " << current_seat_map_[temp_y][temp_x] << "\n";
						checked[6] = true;
						if (current_seat_map_[temp_y][temp_x] == 2) {
							occupied++;
						}
					}
				}
				else { checked[6] = true;
				//std::cout << "down left out of range\n";
				}
			}
			//left
			if (checked[7] == false) {
				temp_x = x - diff;
				if (temp_x >= 0) {
					if (current_seat_map_[y][temp_x]) {
						//std::cout << "current_seat_map_[" << y << "][" << temp_x << "] " << current_seat_map_[y][temp_x] << "\n";
						checked[7] = true;
						if (current_seat_map_[y][temp_x] == 2) {
							occupied++;
						}
					}
				}
				else { checked[7] = true; 
				//std::cout << "left out of range\n";
				}
			}
		}
		//file << "Seat: " << x << " " << y << " :" << occupied << "\n";
		if (occupied >= 5) {
			return 1;
		}
		if (occupied == 0) {
			return 2;
		}
		else {
			return current_seat_map_[y][x];
		}
	}
	return 0;
}


bool Ferry::simulate_simple_round()
{
	//auto file = std::ofstream{ "../../../../Day_11/log.txt" , std::ios::app };
	bool change = false;
	int occupied = 0;
	std::vector<std::vector<int>> new_map;
	for (int y = 0; y < height_; y++) {
		std::vector<int> column{};
		for (int x = 0; x < width_; x++) {
			int temp = check_seat_simple(x, y);
			if (temp == 2) {
				occupied++;
			}
			column.push_back(temp);
			if (temp != current_seat_map_[y][x]) {
				change = true;
			}
		}
		new_map.push_back(column);
	}
	//file << "new round\n\n";
	occupied_ = occupied;
	current_seat_map_ = new_map;
	return change;
}

bool Ferry::simulate_round()
{
	auto file = std::ofstream{ "../../../../Day_11/log.txt" , std::ios::app };
	bool change = false;
	int occupied = 0;
	std::vector<std::vector<int>> new_map;
	for (int y = 0; y < height_; y++) {
		std::vector<int> column{};
		for (int x = 0; x < width_; x++) {
			//std::cout << "checking" << x << " " << y << "\n";
			int temp = check_seat(x, y);
			if (temp == 2) {
				occupied++;
			}
			column.push_back(temp);
			if (temp != current_seat_map_[y][x]) {
				change = true;
			}
		}
		new_map.push_back(column);
	}
	file << "new round\n\n";
	occupied_ = occupied;
	current_seat_map_ = new_map;
	return change;
}

void Ferry::print()
{
	auto file = std::ofstream{ "../../../../Day_11/output.txt" , std::ios::app };
	std::cout << width_ << " " << current_seat_map_.size() << " " << height_ << " " << current_seat_map_[0].size() << "\n";
	for (int y = 0; y < height_; y++) {
		for (int x = 0; x < width_; x++) {
			switch (current_seat_map_[y][x]) {
			case 0: file << '.'; break;
			case 1: file << 'L'; break;
			case 2: file << '#'; break;
			}
		}
		file << "\n";
	}
	file << "\n";
}

int Ferry::part_one()
{
	std::cout << "Part one: \n";
	int round = 0;
	while (simulate_simple_round()) {
		round++;
		std::cout << "round: " << round << " occupied: " << occupied_ << "\n";
		//print();
	}
	return occupied_;
}

int Ferry::part_two()
{
	read_input(filepath_);
	std::cout << "Part two: \n";
	int round = 0;
	while (simulate_round()) {
		round++;
		std::cout << "round: " << round << " occupied: " << occupied_ << "\n";
		//print();
	}
	return occupied_;
}
