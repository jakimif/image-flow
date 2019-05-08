#include "resizemode.h"

#include <stb_image.h>
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_image_resize.h>
#include <stb_image_write.h>

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
	int inputWidth = 0;
	int inputHeight = 0;
	int inputNumComp = 0;
	const int numCompReq = 4;

	if (unsigned char* inputData =
	        stbi_load(filepath.string().c_str(), &inputWidth, &inputHeight, &inputNumComp, numCompReq)) {
		const size_t numOutputPixels = width * height * numCompReq;

		std::vector<std::uint8_t> outputData(numOutputPixels, 0);

		const uint8_t resizeResult = stbir_resize_uint8(inputData, inputWidth, inputHeight, 0,
		                                                outputData.data(), width, height, 0, numCompReq);

		if (resizeResult == 1) {
			int writeResult = 1;
			const std::filesystem::path extension = filepath.extension();
			if (extension == ".jpg") {
				writeResult = stbi_write_jpg(filepath.string().c_str(), width, height, numCompReq,
				                             outputData.data(), 100);

			} else if (extension == ".png") {
				writeResult = stbi_write_png(filepath.string().c_str(), width, height, numCompReq,
				                             outputData.data(), 0);
			} else {
				std::cout << getModeName() << "unsupported format " << filepath << "\n";
			}

			if (writeResult == 0) {
				std::cout << getModeName() << "error writing image " << filepath << "\n";
			}

		} else {
			std::cout << getModeName() << "error when resizing " << filepath << "\n";
		}

		stbi_image_free(inputData);
	} else {
		std::cout << getModeName() << "error loading " << filepath << "\n";
	}
}