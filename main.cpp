#include <iostream>

#include "argumentParser.h"
#include "mode.h"
#include "modesfactory.h"

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
		if (Mode* photoMode = createMode(argParser)) {
			photoMode->run();
		}
	} catch (std::exception& exception) {
		std::cerr << exception.what() << "\n";
	}

	std::cout << "\n";
	return 0;
}