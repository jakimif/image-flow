#include "renamemode.h"

#include <filesystem>
#include <iostream>
#include <vector>

RenameMode::RenameMode(const std::string& filter, const std::string& folder, const std::string& prefix,
                       int start) :
    Mode{filter, folder}, m_prefix{prefix}, m_start{start} {}

const std::string& RenameMode::getModeName() const {
	static const std::string renameModeName = "[Rename]: ";
	return renameModeName;
}

void RenameMode::runImpl() {
	std::cout << getModeName() << "Mode: [rename]\n";
	std::cout << getModeName() << "Folder: " << getFolder() << "\n";
	std::cout << getModeName() << "Filter: " << getFilter() << "\n";
	std::cout << getModeName() << "Prefix: " << m_prefix << "\n";
	std::cout << getModeName() << "Start: " << m_start << "\n";

	std::vector<std::filesystem::path> filesToRename;
	int numSkippedFiles = 0;

	for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(getFolder())) {
		const bool isFile = std::filesystem::is_regular_file(entry.path());
		const bool matchFilter =
		    getFilter().empty() || (entry.path().string().find(getFilter()) != std::string::npos);

		if (isFile && matchFilter) {
			filesToRename.push_back(entry.path());
		} else {
			numSkippedFiles++;
		}
	}

	std::cout << getModeName() << "number of files found: " << filesToRename.size() << "\n";
	std::cout << getModeName() << "numbers of skipped files: " << numSkippedFiles << "\n";

	int startNumber = m_start;
	for (std::filesystem::path& filepath : filesToRename) {
		const std::filesystem::path extension = filepath.extension();
		const std::string newFileName = m_prefix + std::to_string(startNumber++) + extension.string();

		try {
			// rename
			std::filesystem::path newFilePath = filepath;
			newFilePath.replace_filename(newFileName);
			std::filesystem::rename(filepath, newFilePath);
		} catch (const std::exception& exception) {
			std::cerr << getModeName() << "error \"" << filepath << "\":" << exception.what() << "\n";
		}
	}
}