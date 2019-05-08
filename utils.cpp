#include "utils.h"

#include <algorithm>

namespace Utils {
std::string toLower(std::string str) {
	std::transform(std::begin(str), std::end(str), std::begin(str),
	               [](unsigned char c) { return std::tolower(c); });
	return str;
}

std::string toUpper(std::string str) {
	std::transform(std::begin(str), std::end(str), std::begin(str),
	               [](unsigned char c) { return std::toupper(c); });
	return str;
}

bool hasWhitespaces(const std::string& str) { return str.find(' ') != std::string::npos; }

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

} // namespace Utils
