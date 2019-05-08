#include "mode.h"

#include <chrono>
#include <filesystem>
#include <iostream>

Mode::Mode(const std::string& filter, const std::string& folder) : m_filter{filter}, m_folder{folder} {}
const std::string& Mode::getFilter() const { return m_filter; }

const std::string& Mode::getFolder() const { return m_folder; }

void Mode::run() {
	using clock_t = std::chrono::high_resolution_clock;

	clock_t::time_point startTime = clock_t::now();
	runImpl();
	clock_t::time_point endTime = clock_t::now();

	clock_t::duration elapsedTime = endTime - startTime;

	std::chrono::milliseconds elapsedTimeMilliseconds =
	    std::chrono::duration_cast<std::chrono::milliseconds>(elapsedTime);

	std::cout << getModeName() << "operation completed in " << elapsedTimeMilliseconds.count() << "ms\n";
}

std::vector<std::filesystem::path> Mode::getFiles(const std::filesystem::path& extension) const {
	std::vector<std::filesystem::path> files;
	int numSkippedFiles = 0;

	for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(m_folder)) {
		const bool isFile = std::filesystem::is_regular_file(entry.path());
		const bool matchFilter =
		    m_filter.empty() || (entry.path().string().find(m_filter) != std::string::npos);
		const bool matchExtension = extension.empty() || (entry.path().extension() == extension);

		if (isFile && matchFilter && matchExtension) {
			files.push_back(entry.path());
		} else {
			numSkippedFiles++;
		}
	}

	std::cout << getModeName() << "number of files found: " << files.size() << "\n";
	std::cout << getModeName() << "numbers of skipped files: " << numSkippedFiles << "\n";

	return files;
}
