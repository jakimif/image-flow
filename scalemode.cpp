#include "scalemode.h"

#include <stb_image.h>

#include <iostream>

ScaleMode::ScaleMode(const std::string& filter, const std::string& folder, float scaleFactor) :
    ResizeMode{filter, folder}, m_scaleFactor(scaleFactor) {}

const std::string& ScaleMode::getModeName() const {
	static std::string scaleModeName = "[ScaleMode]: ";
	return scaleModeName;
}

void ScaleMode::runImpl() {
	std::cout << getModeName() << "Mode: [scale]\n";
	std::cout << getModeName() << "Folder: " << getFolder() << "\n";
	std::cout << getModeName() << "Filter: " << getFilter() << "\n";
	std::cout << getModeName() << "ScaleFactor: " << m_scaleFactor << "\n";

	for (std::filesystem::path& filepath : getFiles()) {
		std::cout << getModeName() << "scaling " << filepath << "\n";
		int width = 0;
		int height = 0;
		int numComp = 0;

		stbi_info(filepath.string().c_str(), &width, &height, &numComp);

		const int newWidth = static_cast<int>(width * m_scaleFactor);
		const int newHeight = static_cast<int>(height * m_scaleFactor);

		resizeImage(filepath, newWidth, newHeight);
	}
}