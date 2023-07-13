#include "convertmode.h"

#include <filesystem>
#include <iostream>

#include "image.h"
#include "threadpool.h"

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

	ThreadPool pool;

	for (std::filesystem::path& filepath : filesToConvert) {
		pool.enqueue([this, filepath]() {
			std::cout << getModeName() << filepath << "\n";

			const int numReqComp = 3;

			Image image(filepath, numReqComp);
			if (image.isCorrectLoaded()) {
				std::filesystem::path destFilepath = filepath;
				destFilepath.replace_extension(toString(m_toFormat));

				bool writeResult = false;
				switch (m_toFormat) {
					case Format::PNG:
						writeResult = image.writePng(destFilepath);
						break;
					case Format::JPG:
						writeResult = image.writeJpg(destFilepath, 100);
						break;

					default:
						break;
				}

				if (!writeResult) {
					std::cout << getModeName() << "error converting " << filepath << "\n";
				}

			} else {
				std::cout << getModeName() << "error loading " << filepath << "\n";
			}
		});
	}
}
