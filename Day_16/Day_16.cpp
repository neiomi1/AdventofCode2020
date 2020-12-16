#include "Day_16.h"
#include <sstream>

Ticket_ranges::Ticket_ranges(const std::string& filepath) : filepath_(filepath)
{
}

bool Ticket_ranges::contains(int n)
{
	for (auto& [lhs, rhs] : ranges_) {
		if (lhs <= n && rhs >= n) {
			return true;
		}
	}
	return false;
}

bool Ticket_ranges::valid_ticket(std::vector<int>& ticket)
{
	for (auto& elem : ticket) {
		if (!contains(elem)) {
			return false;
		}
	}
	return true;
}

std::vector<int> Ticket_ranges::string_to_ticket(const std::string& string)
{
	auto stream = std::istringstream{ string };
	int n;
	char c;
	std::vector<int> ticket;
	while (stream >> n) {
		ticket.push_back(n);
		stream >> c;
	}
	return ticket;
}

bool Ticket_ranges::trunctuate(std::unordered_map<std::string, std::vector<int>>& possible_indexes)
{
	bool trunctuated = false;
	for (auto& [ticket_field, possible_indexes_vector] : possible_indexes) {
		if (possible_indexes_vector.size() == 1) {
			for (auto& [f, to_erase] : possible_indexes) {
				if (f != ticket_field) {
					auto before = to_erase.size();
					std::erase_if(to_erase, [&](const auto& elem) {return possible_indexes_vector[0] == elem; });
					if (before != to_erase.size()) {
						trunctuated = true;
					}
				}
			}
		}
	}
	return trunctuated;
}


uint64_t Ticket_ranges::part_one()
{
	auto file = std::ifstream{ filepath_ };
	std::string line;
	auto number_capture = std::regex{ "([0-9]+)" };
	//get ranges
	while (std::getline(file, line)) {
		if (line == "your ticket:")
			break;
		int prev = -1;
		std::sregex_iterator numbers(line.begin(), line.end(), number_capture), end_numbers;
		for (; numbers != end_numbers; numbers++) {
			int current_rhs = std::stoi((*numbers)[0]);
			if (prev != -1) {

				bool found = false;
				//speedup for part 1:
				for (auto& [lhs, rhs] : ranges_) {
					if (current_rhs >= lhs && current_rhs <= rhs) {
						if (lhs > prev) {
							lhs = prev;
						}
						found = true;
						break;
					}
					if (prev >= lhs && prev <= rhs) {
						if (rhs < current_rhs) {
							rhs = current_rhs;
						}
						found = true;
						break;
					}
				}
				if (!found) {
					ranges_.push_back({ prev,current_rhs});
				}
				prev = -1;
			}
			else {
				prev = current_rhs;
			}
		}

	}

	//for (auto& [lhs, rhs] : ranges_) {
	//	std::cout << lhs << "-" << rhs << "\n";
	//}

	while (std::getline(file, line)) {
		//std::cout << line << "\n";
		if (line == "nearby tickets:")
			break;
	}

	uint64_t result = 0;
	while (std::getline(file, line)) {
		auto stream = std::istringstream{ line };
		int n;
		char c;
		while (stream >> n) {
			//std::cout << n;
			if (contains(n)) {
				//std::cout << " valid";
				stream >> c;
			}
			else {
				//std::cout << " not valid";
				result += static_cast<uint64_t>(n);
				stream.ignore(9999, '\n');
			}
			//std::cout << "\n";

		}

	}
	return result;
}

uint64_t Ticket_ranges::part_two()
{
	std::vector<std::string> ticket_fields;
	auto file = std::ifstream{ filepath_ };
	std::string line;
	auto number_capture = std::regex{ "([0-9]+)" };
	//get ranges
	while (std::getline(file, line)) {
		if (line == "your ticket:")
			break;
		if (!line.empty()) {
			auto info = line.substr(0, line.find(":"));
			//std::cout << info << "\n";
			ticket_fields.push_back(info);
			int prev = -1;
			std::sregex_iterator numbers(line.begin(), line.end(), number_capture), end_numbers;
			for (; numbers != end_numbers; numbers++) {
				int current_rhs = std::stoi((*numbers)[0]);
				if (prev != -1) {
					input_[info].push_back({ prev, current_rhs });
					prev = -1;
				}
				else {
					prev = current_rhs;
				}
			}
		}

	}

	std::vector<int> my_ticket;
	while (std::getline(file, line)) {
		if (line == "nearby tickets:")
			break;
		if (!line.empty()) {
			my_ticket = string_to_ticket(line);
		}

	}
	//find out ticket ordering:
	std::unordered_map<std::string, std::vector<int>> possible_indexes;
	for (const auto& info : ticket_fields) {
		for (int i = 0; i < std::ssize(my_ticket); i++) {
			possible_indexes[info].push_back(i);
		}
	}

	while (std::getline(file, line)) {
		auto ticket = string_to_ticket(line);
		if (valid_ticket(ticket)) {
			for (int i = 0; i < std::ssize(ticket); i++) {
				for (auto& [ticket_field, possible_indexes_vector] : possible_indexes) {
					bool contains = false;
					for (const auto& ranges : input_[ticket_field]) {
						if (ranges.first <= ticket[i] && ranges.second >= ticket[i]) {
							contains = true;
						}
					}
					if (!contains) {
						std::erase_if(possible_indexes_vector, [&](const auto& elem) {return elem == i; });
					}

					while (trunctuate(possible_indexes)) {}
					//std::cout << ticket_field << " -> " << ticket[i] << "\n";
					//for (const auto& elem : possible_indexes_vector) {
					//	std::cout << elem << " ";
					//}
					//std::cout << "\n";
				}
			}
		}
	}
	uint64_t result =1;
	for (const auto& [fill, indexes] : possible_indexes) {
		//std::cout << fill << ":";
		//for (const auto& elem : indexes) {
		//	std::cout << elem << " ";
		//}
		//std::cout << "\n";
		if (fill.find("departure") != std::string::npos) {
			result *= static_cast<uint64_t>(my_ticket[indexes[0]]);
		}
	}
	return result;
}



