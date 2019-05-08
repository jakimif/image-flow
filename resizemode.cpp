#include "resizemode.h"

#include "image.h"

ResizeMode::ResizeMode(const std::string& filter, const std::string& folder, int width, int height) :
    Mode{filter, folder}, m_width(width), m_height(height) {}

const std::string& ResizeMode::getModeName() const {
	static const std::string renameModeName = "[Resize]: ";
	return renameModeName;
}

void ResizeMode::runImpl() {
	std::cout << getModeName() << "Mode: [resize]\n";
	std::cout << getModeName() << "Folder: " << getFolder() << "\n";
	std::cout << getModeName() << "Filter: " << getFilter() << "\n";
	std::cout << getModeName() << "Width: " << m_width << "\n";
	std::cout << getModeName() << "Height: " << m_height << "\n";

	if (m_width > 0 && m_height > 0) {
		for (std::filesystem::path& filepath : getFiles()) {
			std::cout << getModeName() << "resizing " << filepath << "\n";
			resizeImage(filepath, m_width, m_height);
		}
	}
}

void ResizeMode::resizeImage(const std::filesystem::path filepath, int width, int height) const {
	const int numCompReq = 4;

	Image image(filepath, numCompReq);
	if (image.isCorrectLoaded()) {
		unsigned char* inputData = image.getImageData();
		const size_t numOutputPixels = width * height * numCompReq;
		std::vector<std::uint8_t> outputData(numOutputPixels, 0);

		ImageData* imgData = new ImageData{width, height, numCompReq};

		bool isSuccessResizeResult = image.resize(inputData, outputData, width, height, numCompReq);

		if (isSuccessResizeResult) {
			bool writeResult = false;
			const std::filesystem::path extension = filepath.extension();
			if (extension == ".jpg") {
				writeResult = image.writeJpg(filepath, 100, imgData, outputData);

			} else if (extension == ".png") {
				writeResult = image.writePng(filepath, imgData, outputData);
			} else {
				std::cout << getModeName() << "unsupported format " << filepath << "\n";
			}

			if (!writeResult) {
				std::cout << getModeName() << "error writing image " << filepath << "\n";
			}

		} else {
			std::cout << getModeName() << "error when resizing " << filepath << "\n";
		}

		delete imgData;

	} else {
		std::cout << getModeName() << "error loading " << filepath << "\n";
	}
}