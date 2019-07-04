#include "argumentParser.h"

#include <array>
#include <iomanip>
#include <iostream>

namespace Args {
namespace Flags {
static const char* Rename = "rename";
static const char* Convert = "convert";
static const char* Resize = "resize";
static const char* Scale = "scale";
} // namespace Flags
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
		throw std::invalid_argument("Somente um modo pode estar ativo.");
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
}

int main(int argc, char* argv[]) {
	ArgumentParser argParser;

	argParser.registerFlag(Args::Flags::Rename);
	argParser.registerFlag(Args::Flags::Convert);
	argParser.registerFlag(Args::Flags::Resize);
	argParser.registerFlag(Args::Flags::Scale);

	argParser.registerOption("folder");
	argParser.registerOption("amount");

	argParser.parse(argc, argv);

	// std::cout << "Folder: " << argParser.getOptionAs<std::string>("folder") << "\n";
	// std::cout << "Amount: " << argParser.getOptionAs<float>("amount") << "\n";
	// std::cout << "Amount: " << argParser.getOptionAs<int>("amount") << "\n";

	try {
		validateArguments(argParser);
	} catch (std::exception& exception) {
		std::cerr << exception.what() << "\n";
	}

	std::cout << "\n";
	return 0;
}