#include "convertmode.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

#include <filesystem>
#include <iostream>

std::string toString(ConvertMode::Format format) {
	switch (format) {
		case ConvertMode::Format::JPG:
			return "jpg";
		case ConvertMode::Format::PNG:
			return "png";
		default:
			return "";
	}
}

std::ostream& operator<<(std::ostream& out, ConvertMode::Format format) {
	out << toString(format);
	return out;
}

ConvertMode::ConvertMode(const std::string& filter, const std::string& folder, Format from, Format to) :
    Mode{filter, folder}, m_fromFormat{from}, m_toFormat{to} {}

const std::string& ConvertMode::getModeName() const {
	static std::string convertModeName = "[Convert]: ";
	return convertModeName;
}

void ConvertMode::runImpl() {
	std::cout << getModeName() << "Mode: [convert]\n";
	std::cout << getModeName() << "Folder: " << getFolder() << "\n";
	std::cout << getModeName() << "Filter: " << getFilter() << "\n";
	std::cout << getModeName() << "From: " << m_fromFormat << "\n";
	std::cout << getModeName() << "To: " << m_toFormat << "\n";

	const std::filesystem::path fromExtension = "." + toString(m_fromFormat);
	const std::filesystem::path toExtension = "." + toString(m_toFormat);

	std::vector<std::filesystem::path> filesToConvert = getFiles(fromExtension);

	for (std::filesystem::path& filepath : filesToConvert) {
		std::cout << getModeName() << filepath << "\n";

		int width = 0;
		int height = 0;
		int numComp = 0;
		const int numReqComp = 3;

		// 0 ~ 255
		if (unsigned char* data =
		        stbi_load(filepath.string().c_str(), &width, &height, &numComp, numReqComp)) {
			std::filesystem::path destFilepath = filepath;
			destFilepath.replace_extension(toString(m_toFormat));

			int writeResult = 0;
			switch (m_toFormat) {
				case Format::PNG:
					writeResult =
					    stbi_write_png(destFilepath.string().c_str(), width, height, numComp, data, 0);
					break;
				case Format::JPG:
					writeResult =
					    stbi_write_jpg(destFilepath.string().c_str(), width, height, numComp, data, 50);
					break;

				default:
					break;
			}

			if (writeResult == 0) {
				std::cout << getModeName() << "error converting " << filepath << "\n";
			}

			stbi_image_free(data);
		} else {
			std::cout << getModeName() << "error loading " << filepath << "\n";
		}
	}
}
