#ifndef ARGUMENT_PARSER_H
#define ARGUMENT_PARSER_H

#include <iostream>
#include <map>

class ArgumentParser {
private:
	std::map<std::string, bool> m_flags;
	std::map<std::string, std::string> m_options;
	const std::string& getOption(const std::string& option) const;
	float getOptionAsFloat(const std::string& option) const;
	int getOptionAsInt(const std::string& option) const;

public:
	void registerFlag(const std::string& flag);
	bool getFlag(const std::string& flag) const;
	void parse(int argc, char* argv[]);
	void registerOption(const std::string& option);
	bool isFlagRegistered(const std::string& flag) const;
	bool isOptionRegistered(const std::string& option) const;

	template <typename T>
	T getOptionAs(const std::string& option) const;

	template <>
	std::string getOptionAs(const std::string& option) const {
		return getOption(option);
	}

	template <>
	float getOptionAs(const std::string& option) const {
		return getOptionAsFloat(option);
	}

	template <>
	int getOptionAs(const std::string& option) const {
		return getOptionAsInt(option);
	}
};

#endif