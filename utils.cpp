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
} // namespace Utils
