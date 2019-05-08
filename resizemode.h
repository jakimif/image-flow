#ifndef RESIZE_MODE_H
#define RESIZE_MODE_H

#include <filesystem>

#include "mode.h"

class ResizeMode : public Mode {
public:
	ResizeMode(const std::string& filter, const std::string& folder, int width = -1, int height = -1);
	const std::string& getModeName() const override;

protected:
	void runImpl() override;
	void resizeImage(const std::filesystem::path filepath, int width, int height) const;

private:
	int m_width;
	int m_height;
};

#endif