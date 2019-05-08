#ifndef SCALE_MODE_H
#define SCALE_MODE_H

#include "resizemode.h"

class ScaleMode final : public ResizeMode {
public:
	ScaleMode(const std::string& filter, const std::string& folder, float scaleFactor);
	const std::string& getModeName() const override;

protected:
	void runImpl() override;

private:
	float m_scaleFactor;
};

#endif