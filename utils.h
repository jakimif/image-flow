#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace Utils {
std::string toLower(std::string str);
std::string toUpper(std::string str);
bool hasWhitespaces(const std::string& str);
const std::string& getInvalidChars();
bool hasInvalidChars(const std::string& str);
}; // namespace Utils

#endif