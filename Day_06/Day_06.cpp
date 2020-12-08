#include "Day_06.h"
#include <vector>
#include <fstream>
#include <algorithm>
#include <chrono>
#include <unordered_map>
#include <sstream>


void read_entries(const std::string& filename, std::vector<DeclarationForm>& declaration_forms) {
	auto file = std::ifstream{ "..\\..\\..\\..\\Day_06\\" + filename };
	std::string line;
	int num_people = 0;
	auto declaration_form = DeclarationForm{};
	while (std::getline(file, line)){
		if (line.empty()) {
			declaration_form.number_of_people = num_people;
			declaration_forms.push_back(declaration_form);
			declaration_form = DeclarationForm{};
			num_people = 0;
		}
		else {
			for (const auto& c : line) {
				declaration_form.answers[c]++;
			}
			num_people++;
		}
	}
	if (!declaration_form.answers.empty()) {
		declaration_form.number_of_people = num_people;
		declaration_forms.push_back(declaration_form);
	}
}

int sum_answers_anyone(const std::vector<DeclarationForm>& declaration_forms) {
	int sum = 0;
	std::for_each(declaration_forms.begin(), declaration_forms.end(), [&](const auto& entry) {sum += (int)std::ssize(entry.answers); });
	return sum;
}

int sum_answers_everyone(const std::vector<DeclarationForm>& declaration_forms, bool noisy = false) {
	int sum = 0;
	std::ofstream file_out;
	if (noisy) {
		file_out = std::ofstream{ "../../../../Day_06/output.txt" };
	}
	std::for_each(declaration_forms.begin(), declaration_forms.end(), [&](const auto& entry) {
		if (noisy) {
			file_out << "Number of people " << entry.number_of_people << "\n";
		}
		for (const auto& [answer, amount] : entry.answers) {
			if (noisy) {
				file_out << answer << " " << amount << "\n";
			}
			
			if (amount == entry.number_of_people) { sum++; }
		}
		if(noisy){ file_out << "\n"; }
		});
	return sum;
}



int main()
{
	auto declaration_forms = std::vector<DeclarationForm>{};

	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_06\\execution_times.txt" };
	auto start = std::chrono::high_resolution_clock::now();
	read_entries("input.txt", declaration_forms);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Input read and parsed in: " << duration.count() << " microseconds.\n";
	
	start = std::chrono::high_resolution_clock::now();
	int answer_sum = sum_answers_anyone(declaration_forms);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Sum of all anyone answers calculated in: " << duration.count() << " microseconds.\n";
	
	std::cout <<"Sum of all anyone answers: "<< answer_sum << "\n";
	
	start = std::chrono::high_resolution_clock::now();
	answer_sum = sum_answers_everyone(declaration_forms);
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Number of all everyone answers calculated in: " << duration.count() << " microseconds.";
	
	std::cout << "Number of all anyone answers: " << answer_sum << "\n";

}
