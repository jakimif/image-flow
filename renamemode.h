#ifndef RENAME_MODE_H
#define RENAME_MODE_H

#include "mode.h"

class RenameMode final : public Mode {
public:
	RenameMode(const std::string& filter, const std::string& folder, const std::string& prefix, int start);
	const std::string& getModeName() const override;

protected:
	void runImpl() override;

private:
	std::string m_prefix;
	int m_start;
};

#endif