#include <chrono>
#include "Day_08.h"
#include <fstream>

int main()
{

	auto file_time = std::ofstream{ "..\\..\\..\\..\\Day_08\\execution_times.txt" };
	auto start = std::chrono::high_resolution_clock::now();
	GameConsole handheld = GameConsole("../../../../Day_08/input.txt");
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Input read and parsed in: " << duration.count() << " microseconds.\n";

	start = std::chrono::high_resolution_clock::now();
	int answer_part_one = handheld.run_until_loop();
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Part one calculated in: " << duration.count() << " microseconds.\n";

	std::cout << "Part one answer: " << answer_part_one << "\n";

	start = std::chrono::high_resolution_clock::now();
	int answer_part_two = handheld.fix_run();
	stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	file_time << "Part two calculated in: " << duration.count() << " microseconds.";

	std::cout << "Part two answer: " << answer_part_two << "\n";

}
