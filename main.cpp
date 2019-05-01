#include "argumentParser.h"

#include <array>
#include <filesystem>
#include <iomanip>
#include <iostream>

namespace Args {
namespace Flags {
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
} // namespace Opts
} // namespace Args

void validateArguments(const ArgumentParser& argParser) {
	// verificar se somente um modo (flag) está ativo
	// verificar se o usuário não esta passando varias flags
	const bool bRenameMode = argParser.getFlag(Args::Flags::Rename);
	const bool bConvertMode = argParser.getFlag(Args::Flags::Convert);
	const bool bResizeMode = argParser.getFlag(Args::Flags::Resize);
	const bool bScaleMode = argParser.getFlag(Args::Flags::Scale);

	const std::vector<bool> modes = {bRenameMode, bConvertMode, bResizeMode, bScaleMode};
	const std::ptrdiff_t numActiveModes = std::count(std::begin(modes), std::end(modes), true);

	std::cout << std::boolalpha << "Rename: " << argParser.getFlag(Args::Flags::Rename) << "\n";
	std::cout << std::boolalpha << "Convert: " << argParser.getFlag(Args::Flags::Convert) << "\n";
	std::cout << std::boolalpha << "Resize: " << argParser.getFlag(Args::Flags::Resize) << "\n";
	std::cout << std::boolalpha << "Scale: " << argParser.getFlag(Args::Flags::Scale) << "\n";

	if (numActiveModes != 1) {
		throw std::invalid_argument("only one mode can be active.");
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
	if (!filter.empty()) {
		std::string invalidCaracteres = "\\/*?\"<>|"; // \/*?"<>|
		if (filter.find_first_of(invalidCaracteres) != std::string::npos) {
			throw std::invalid_argument("the filter cannot contain: " + invalidCaracteres);
		}
	}

	// validar o modo resize
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

	// validar scale mode
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
}

int main(int argc, char* argv[]) {
	ArgumentParser argParser;

	argParser.registerFlag(Args::Flags::Rename);
	argParser.registerFlag(Args::Flags::Convert);
	argParser.registerFlag(Args::Flags::Resize);
	argParser.registerFlag(Args::Flags::Scale);

	argParser.registerOption(Args::Opts::Folder);
	argParser.registerOption(Args::Opts::Filter);
	argParser.registerOption(Args::Opts::Width);
	argParser.registerOption(Args::Opts::Height);
	argParser.registerOption(Args::Opts::Amount);

	argParser.parse(argc, argv);

	try {
		validateArguments(argParser);
	} catch (std::exception& exception) {
		std::cerr << exception.what() << "\n";
	}

	std::cout << "\n";
	return 0;
}