#include "argumentParser.h"

#include "utils.h"

#include <algorithm>
#include <iostream>

void ArgumentParser::registerFlag(const std::string& flag) {
	if (!flag.empty() && !Utils::hasWhitespaces(flag)) {
		m_flags[flag] = false;
	}
}

bool ArgumentParser::getFlag(const std::string& flag) const {
	if (!flag.empty()) {
		auto flagIt = m_flags.find(flag);
		if (flagIt != std::end(m_flags)) {
			return flagIt->second;
		}
		return false;
	}

	return false;
}

void ArgumentParser::registerOption(const std::string& option) {
	if (!option.empty() && !Utils::hasWhitespaces(option)) {
		m_options[option] = "";
	}
}

bool ArgumentParser::isFlagRegistered(const std::string& flag) const {
	if (!flag.empty()) {
		return m_flags.count(flag) == 1;
	}

	return false;
}

bool ArgumentParser::isOptionRegistered(const std::string& option) const {
	if (!option.empty()) {
		return m_options.count(option) == 1;
	}

	return false;
}

const std::string& ArgumentParser::getOption(const std::string& option) const {
	if (!option.empty()) {
		auto optionIt = m_options.find(option);
		if (optionIt != std::end(m_options)) {
			return optionIt->second;
		}
	}

	static std::string EmptyOption = "";
	return EmptyOption;
}

float ArgumentParser::getOptionAsFloat(const std::string& option) const {
	const std::string& optionValue = getOption(option);

	if (!optionValue.empty()) {
		return std::stof(optionValue);
	}

	return -1;
}

int ArgumentParser::getOptionAsInt(const std::string& option) const {
	const std::string& optionValue = getOption(option);

	if (!optionValue.empty()) {
		return std::stoi(optionValue);
	}

	return -1;
}

void ArgumentParser::parse(int argc, char* argv[]) {
	if (argc > 1 && argv != nullptr) {
		for (int i = 1; i < argc; i++) {
			// std::string arg = argv[i];
			std::string arg = Utils::toLower(argv[i]);

			if (arg.length() >= 3) {
				// prefix --
				if (arg[0] == '-' && arg[1] == '-') {
					// remover os -- da string (flag)
					arg = arg.substr(2);
					if (arg.find_first_of('=') != std::string::npos) {
						// Isso é uma opção
						const size_t equalsSignPos = arg.find('=');
						if (equalsSignPos != std::string::npos) {
							std::string optionName = arg.substr(0, equalsSignPos);
							std::string optionValue = arg.substr(equalsSignPos + 1);

							auto optionIt = m_options.find(optionName);
							if (optionIt != std::end(m_options)) {
								optionIt->second = optionValue;
							}
						}
					} else {
						// é uma flag
						auto flagIt = m_flags.find(arg);
						if (flagIt != std::end(m_flags)) {
							// Achamos a flag registrada
							flagIt->second = true;
						}
					}
				}
			}
		}
	}
}