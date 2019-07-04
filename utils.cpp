#include "utils.h"

#include <algorithm>

namespace Utils {
std::string toLower(std::string str) {
	std::transform(std::begin(str), std::end(str), std::begin(str),
	               [](unsigned char c) { return std::tolower(c); });
	return str;
}
} // namespace Utils
