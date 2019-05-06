#include "mode.h"

#include <array>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <set>

#include "argumentParser.h"
#include "convertmode.h"
#include "renamemode.h"

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

const std::string& getInvalidChars() {
	static const std::string invalidCaracteres = "\\/*?\"<>|"; // \/*?"<>|
	return invalidCaracteres;
}

bool hasInvalidChars(const std::string& str) {
	if (str.find_first_of(getInvalidChars()) != std::string::npos) {
		return true;
	}

	return false;
}

Mode* createMode(const ArgumentParser& argParser) {
	const bool bHelpMode = argParser.getFlag(Args::Flags::Help);
	const bool bRenameMode = argParser.getFlag(Args::Flags::Rename);
	const bool bConvertMode = argParser.getFlag(Args::Flags::Convert);
	const bool bResizeMode = argParser.getFlag(Args::Flags::Resize);
	const bool bScaleMode = argParser.getFlag(Args::Flags::Scale);

	const std::array<bool, 5> modes = {bHelpMode, bRenameMode, bConvertMode, bResizeMode, bScaleMode};
	const std::ptrdiff_t numActiveModes = std::count(std::begin(modes), std::end(modes), true);

	if (numActiveModes != 1) {
		throw std::invalid_argument("only one mode can be active.");
	}

	if (bHelpMode) {
		std::filesystem::path filePath("./help.txt");

		if (std::filesystem::exists(filePath)) {
			std::ifstream inputFile(filePath);
			if (!inputFile.is_open()) {
				std::cout << "Não foi possível abrir o arquivo." << std::endl;
				throw std::invalid_argument("filter cannot be blank in scale mode.");
			}

			std::string line;
			while (std::getline(inputFile, line)) {
				std::cout << line << std::endl;
			}
			inputFile.close();
		} else {
			std::cout << "O arquivo não existe." << std::endl;
			throw std::invalid_argument("O arquivo não existe.");
		}
	}

	const std::string folder = argParser.getOptionAs<std::string>(Args::Opts::Folder);
	if (folder.empty()) {
		throw std::invalid_argument("the folder cannot be blank.");
	}

	if (!std::filesystem::exists(folder)) {
		throw std::invalid_argument("the folder does not exist.");
	}

	const std::string filter = argParser.getOptionAs<std::string>(Args::Opts::Filter);
	if (!filter.empty() && hasInvalidChars(filter)) {
		throw std::invalid_argument("the filter cannot contain: " + getInvalidChars());
	}

	if (bResizeMode) {
		int width = 0;
		int height = 0;

		try {
			width = argParser.getOptionAs<int>(Args::Opts::Width);
			height = argParser.getOptionAs<int>(Args::Opts::Height);
		} catch (const std::invalid_argument&) {
			throw std::invalid_argument("the value entered for width or height are not valid numbers.");
		}

		if (width <= 0 || height <= 0) {
			throw std::invalid_argument("width and height must be greater than zero.");
		}

		if (filter.empty()) {
			throw std::invalid_argument("filter cannot be blank in resize mode.");
		}
	}

	if (bScaleMode) {
		float amount = 0.0f;

		try {
			amount = argParser.getOptionAs<float>(Args::Opts::Amount);
		} catch (const std::invalid_argument&) {
			throw std::invalid_argument("the value entered for quantity is not a valid number.");
		}

		if (amount <= 0.0f) {
			throw std::invalid_argument("amount must be greater than zero.");
		}

		if (filter.empty()) {
			throw std::invalid_argument("filter cannot be blank in scale mode.");
		}
	}

	if (bRenameMode) {
		std::string prefix = argParser.getOptionAs<std::string>(Args::Opts::Prefix);
		int start = -1;

		try {
			start = argParser.getOptionAs<int>(Args::Opts::Start);
		} catch (const std::invalid_argument&) {
			throw std::invalid_argument("the value entered for start is not a valid number.");
		}

		if (prefix.empty()) {
			throw std::invalid_argument("prefix needs to be informed.");
		}

		if (hasInvalidChars(prefix)) {
			throw std::invalid_argument("the prefix cannot contain: " + getInvalidChars());
		}

		if (start < 0) {
			throw std::invalid_argument("start needs to be greater than zero.");
		}

		Mode* ptr = new RenameMode(filter, folder, prefix, start);
		return ptr;
	}

	if (bConvertMode) {
		const std::string from = argParser.getOptionAs<std::string>(Args::Opts::From);
		const std::string to = argParser.getOptionAs<std::string>(Args::Opts::To);
		const std::set<std::string> convertOptions = {"jpg", "png"};

		auto it = convertOptions.find(from);
		const bool bIsFromValid = it != convertOptions.end();

		it = convertOptions.find(to);
		const bool bIsToValid = it != convertOptions.end();

		if (!bIsFromValid || !bIsToValid) {
			throw std::invalid_argument("from and to must be jpeg or png.");
		}

		if (from == to) {
			throw std::invalid_argument("from and to must be different.");
		}

		const std::map<std::string, ConvertMode::Format> convertOptionsMap = {
		    {"jpg", ConvertMode::Format::JPG},
		    {"png", ConvertMode::Format::PNG},
		};

		Mode* ptr = new ConvertMode(filter, folder, convertOptionsMap.at(from), convertOptionsMap.at(to));
		return ptr;
	}

	return nullptr;
}