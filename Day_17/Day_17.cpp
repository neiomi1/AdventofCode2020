#include "Day_17.h"
#include <sstream>

Cube_map::Cube_map(const std::string& filepath) : filepath_(filepath)
{
}

void Cube_map::read_start()
{
	auto file = std::ifstream{ filepath_ };
	long x = 0;
	long y = 0;
	long z = 0;
	long w = 0;
	std::string line;
	while (std::getline(file, line)) {
		auto stream = std::istringstream{ line };
		for (const auto& c : line) {
			if (c == '#') {
				cubes_.insert(coordinates_3D{ x,y,z });
				hypercubes_.insert(coordinates_4D{ x,y,z,w });
			}
			x++;
		}
		x = 0;
		y++;
	}

	std::cout << "round " << round_ << ": " << cubes_.size() << "\n";
}

void Cube_map::calculate_round_3D()
{
	round_++;

	std::set<coordinates_3D> next_round{};
	std::set<coordinates_3D> checked{};

	for (const auto& cube : cubes_) {
		for (long x = cube.x - 1; x <= cube.x + 1; x++) {
			for (long y = cube.y - 1; y <= cube.y + 1; y++) {
				for (long z = cube.z - 1; z <= cube.z + 1; z++) {
					auto coords = coordinates_3D{ x,y,z };
					if (!checked.contains(coords)) {
						checked.insert(coords);
						//check cube surroundings
						int count = 0;
						for (long x_ = x - 1; x_ <= x + 1 && count < 4; x_++) {
							for (long y_ = y - 1; y_ <= y + 1 && count < 4; y_++) {
								for (long z_ = z - 1; z_ <= z + 1 && count < 4; z_++) {
									auto to_check = coordinates_3D{ x_,y_,z_ };
									if (coords != to_check && cubes_.contains(to_check)) {
										count++;
									}
								}
							}
						}

						if (cubes_.contains(coords) && (count == 2 || count == 3)) {
							next_round.insert(coords);
						}
						else if (!cubes_.contains(coords) && count == 3) {
							next_round.insert(coords);
						}
					}
				}
			}
		}
	}
	cubes_ = next_round;
	std::cout << "round " << round_ << ": " << cubes_.size() << "\n";
}


void Cube_map::calculate_round_4D()
{
	round_++;

	std::set<coordinates_4D> next_round{};
	std::set<coordinates_4D> checked{};

	for (const auto& cube : hypercubes_) {
		for (long x = cube.x - 1; x <= cube.x + 1; x++) {
			for (long y = cube.y - 1; y <= cube.y + 1; y++) {
				for (long z = cube.z - 1; z <= cube.z + 1; z++) {
					for (long w = cube.w - 1; w <= cube.w + 1; w++) {
						auto coords = coordinates_4D{ x,y,z,w };
						if (!checked.contains(coords)) {
							checked.insert(coords);
							//check cube surroundings
							int count = 0;
							for (long x_ = x - 1; x_ <= x + 1 && count < 4; x_++) {
								for (long y_ = y - 1; y_ <= y + 1 && count < 4; y_++) {
									for (long z_ = z - 1; z_ <= z + 1 && count < 4; z_++) {
										for (long w_ = w - 1; w_ <= w + 1 && count < 4; w_++) {
											auto to_check = coordinates_4D{ x_,y_,z_,w_};
											if (coords != to_check && hypercubes_.contains(to_check)) {
												count++;
											}
										}
									}
								}
							}
							if (hypercubes_.contains(coords) && (count == 2 || count == 3)) {
								next_round.insert(coords);
							}
							else if (!hypercubes_.contains(coords) && count == 3) {
								next_round.insert(coords);
							}
						}
					}
				}
			}
		}
	}
	hypercubes_ = next_round;
	std::cout << "round " << round_ << ": " << hypercubes_.size() << "\n";
}



uint64_t Cube_map::part_one()
{
	read_start();
	while (round_ < 6){
		calculate_round_3D();
	}
	std::cout << "\n\n";
	return std::ssize(cubes_);
}

uint64_t Cube_map::part_two()
{
	round_ = 0;

	while (round_ < 6) {
		calculate_round_4D();
	}
	return std::ssize(hypercubes_);
}
