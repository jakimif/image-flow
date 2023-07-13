#include "image.h"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_image.h>
#include <stb_image_resize.h>
#include <stb_image_write.h>

#include <iostream>

Image::Image() : m_data{nullptr}, m_numReqComp{0} {}

Image::Image(std::filesystem::path filepath, const int numReqComp) :
    m_filepath(filepath), m_numReqComp(numReqComp) {
	if ((m_data = stbi_load(filepath.string().c_str(), &m_width, &m_height, &m_numComp, numReqComp))) {
		m_isCorrectLoaded = true;
	}
}

Image::~Image() {
	if (m_data) {
		stbi_image_free(m_data);
	}
}

void Image::getInfo(std::filesystem::path filepath, int& width, int& height, int& numComp) const {
	stbi_info(filepath.string().c_str(), &width, &height, &numComp);
}

unsigned char* Image::getImageData() const { return m_data; }

bool Image::isCorrectLoaded() const { return m_isCorrectLoaded; }

bool Image::writePng(std::filesystem::path destFilepath, const ImageData* imageData,
                     const std::vector<unsigned char>& outputData) {
	int writeResult = 0;

	if (imageData) {
		m_width = imageData->width;
		m_height = imageData->height;
		m_numComp = imageData->numComp;
	}

	if (outputData.empty()) {
		writeResult = stbi_write_png(destFilepath.string().c_str(), m_width, m_height, m_numComp, m_data, 0);
	} else {
		writeResult =
		    stbi_write_png(destFilepath.string().c_str(), m_width, m_height, m_numComp, outputData.data(), 0);
	}

	return writeResult != 0;
}

bool Image::writeJpg(std::filesystem::path destFilepath, int quality, const ImageData* imageData,
                     const std::vector<unsigned char>& outputData) {
	int writeResult = 0;

	if (imageData) {
		m_width = imageData->width;
		m_height = imageData->height;
		m_numComp = imageData->numComp;
	}

	if (outputData.empty()) {
		writeResult =
		    stbi_write_jpg(destFilepath.string().c_str(), m_width, m_height, m_numComp, m_data, quality);
	} else {
		writeResult = stbi_write_jpg(destFilepath.string().c_str(), m_width, m_height, m_numComp,
		                             outputData.data(), quality);
	}

	return writeResult != 0;
}

bool Image::resize(unsigned char* inputData, std::vector<unsigned char>& outputData, int out_width,
                   int out_height, int comp) {
	const uint8_t resizeResult = stbir_resize_uint8(inputData, m_width, m_height, 0, outputData.data(),
	                                                out_width, out_height, 0, comp);

	return resizeResult == 1;
}