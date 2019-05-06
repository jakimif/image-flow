#ifndef CONVERT_MODE_H
#define CONVERT_MODE_H

#include "mode.h"

class ConvertMode final : public Mode {
public:
	enum class Format { JPG, PNG };
	ConvertMode(const std::string& filter, const std::string& folder, Format from, Format to);
	const std::string& getModeName() const override;

protected:
	void runImpl() override;

private:
	Format m_fromFormat;
	Format m_toFormat;
};

#endif