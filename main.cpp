#include "argumentParser.h"
#include "mode.h"

#include <array>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <set>

namespace Args {
namespace Flags {
static constexpr const char* Help = "help";
static constexpr const char* Rename = "rename";
static constexpr const char* Convert = "convert";
static constexpr const char* Resize = "resize";
static constexpr const char* Scale = "scale";
} // namespace Flags
namespace Opts {
static constexpr const char* Folder = "folder";
static constexpr const char* Filter = "filter";
static constexpr const char* Width = "width";
static constexpr const char* Height = "height";
static constexpr const char* Amount = "amount";
static constexpr const char* Prefix = "prefix";
static constexpr const char* Start = "start";
static constexpr const char* From = "from";
static constexpr const char* To = "to";
} // namespace Opts
} // namespace Args

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

void validateArguments(const ArgumentParser& argParser) {
	// verificar se somente um modo (flag) está ativo
	// verificar se o usuário não esta passando varias flags

	const bool bHelpMode = argParser.getFlag(Args::Flags::Help);
	const bool bRenameMode = argParser.getFlag(Args::Flags::Rename);
	const bool bConvertMode = argParser.getFlag(Args::Flags::Convert);
	const bool bResizeMode = argParser.getFlag(Args::Flags::Resize);
	const bool bScaleMode = argParser.getFlag(Args::Flags::Scale);

	const std::array<bool, 5> modes = {bHelpMode, bRenameMode, bConvertMode, bResizeMode, bScaleMode};
	const std::ptrdiff_t numActiveModes = std::count(std::begin(modes), std::end(modes), true);

	std::cout << std::boolalpha << "Rename: " << argParser.getFlag(Args::Flags::Rename) << "\n";
	std::cout << std::boolalpha << "Convert: " << argParser.getFlag(Args::Flags::Convert) << "\n";
	std::cout << std::boolalpha << "Resize: " << argParser.getFlag(Args::Flags::Resize) << "\n";
	std::cout << std::boolalpha << "Scale: " << argParser.getFlag(Args::Flags::Scale) << "\n";

	if (numActiveModes != 1) {
		throw std::invalid_argument("only one mode can be active.");
	}

	if (bHelpMode) {
		std::filesystem::path filePath("./help.txt");

		if (std::filesystem::exists(filePath)) {
			std::ifstream inputFile(filePath);
			if (!inputFile.is_open()) {
				std::cout << "Não foi possível abrir o arquivo." << std::endl;
				return;
			}

			std::string line;
			while (std::getline(inputFile, line)) {
				std::cout << line << std::endl;
			}
			inputFile.close();
		} else {
			std::cout << "O arquivo não existe." << std::endl;
			return;
		}
		return;
	}

	// verificar se existem apenas 1 modo, utilizando OR Exclusivo
	// OR Exclusivo só é verdeiro se apenas *UMA* opção for verdadeira
	// 1 ^ 1 = 0
	// 1 ^ 0 = 1
	// 0 ^ 0 = 0

	// se houver mais de um movo ativo lança uma exceção
	// if (!(bRenameMode ^ bConvertMode ^ bResizeMode ^ bScaleMode)) {
	// 	throw std::invalid_argument("Somente um modo pode estar ativo.");
	// }

	// validar a pasta passada como a opção folder
	const std::string folder = argParser.getOptionAs<std::string>(Args::Opts::Folder);
	if (folder.empty()) {
		throw std::invalid_argument("the folder cannot be blank.");
	}

	if (!std::filesystem::exists(folder)) {
		throw std::invalid_argument("the folder does not exist.");
	}

	// validar se o filtro é uma string valida
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

		// const bool bIsFromValid =
		//     std::find(std::begin(convertOptions), std::end(convertOptions), from) !=
		//     std::end(convertOptions);
	}
}

int main(int argc, char* argv[]) {
	ArgumentParser argParser;

	argParser.registerFlag(Args::Flags::Help);
	argParser.registerFlag(Args::Flags::Rename);
	argParser.registerFlag(Args::Flags::Convert);
	argParser.registerFlag(Args::Flags::Resize);
	argParser.registerFlag(Args::Flags::Scale);

	argParser.registerOption(Args::Opts::Folder);
	argParser.registerOption(Args::Opts::Filter);
	argParser.registerOption(Args::Opts::Width);
	argParser.registerOption(Args::Opts::Height);
	argParser.registerOption(Args::Opts::Amount);
	argParser.registerOption(Args::Opts::Prefix);
	argParser.registerOption(Args::Opts::Start);
	argParser.registerOption(Args::Opts::From);
	argParser.registerOption(Args::Opts::To);

	argParser.parse(argc, argv);

	try {
		validateArguments(argParser);
	} catch (std::exception& exception) {
		std::cerr << exception.what() << "\n";
	}

	std::cout << "\n";
	return 0;
}