#include "modesfactory.h"

#include <array>
#include <set>

#include "argumentParser.h"
#include "convertmode.h"
#include "renamemode.h"
#include "resizemode.h"
#include "scalemode.h"
#include "utils.h"

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
		argParser.getHelp();
		return nullptr;
	}

	const std::string folder = argParser.getOptionAs<std::string>(Args::Opts::Folder);
	if (folder.empty()) {
		throw std::invalid_argument("the folder cannot be blank.");
	}

	if (!std::filesystem::exists(folder)) {
		throw std::invalid_argument("the folder does not exist.");
	}

	const std::string filter = argParser.getOptionAs<std::string>(Args::Opts::Filter);
	if (!filter.empty() && Utils::hasInvalidChars(filter)) {
		throw std::invalid_argument("the filter cannot contain: " + Utils::getInvalidChars());
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

		Mode* ptr = new ResizeMode(filter, folder, width, height);
		return ptr;
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

		Mode* ptr = new ScaleMode(filter, folder, amount);
		return ptr;
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

		if (Utils::hasInvalidChars(prefix)) {
			throw std::invalid_argument("the prefix cannot contain: " + Utils::getInvalidChars());
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