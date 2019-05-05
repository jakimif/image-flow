#include "renamemode.h"

#include <iostream>

RenameMode::RenameMode(const std::string& filter, const std::string& folder, const std::string& prefix,
                       int start) :
    Mode{filter, folder}, m_prefix{prefix}, m_start{start} {}

const std::string& RenameMode::getModeName() const {
	static const std::string renameModeName = "[Rename]: ";
	return renameModeName;
}

void RenameMode::runImpl() { std::cout << getModeName() << "is running\n"; }