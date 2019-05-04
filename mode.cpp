#include "mode.h"

Mode::Mode(const std::string& filter, const std::string& folder) : m_filter{filter}, m_folder{folder} {}

const std::string& Mode::getFilter() const { return m_filter; }

const std::string& Mode::getFolder() const { return m_folder; }

void Mode::run() { runImpl(); }