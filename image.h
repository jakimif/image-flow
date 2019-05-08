#ifndef IMAGE_H
#define IMAGE_H

#include <filesystem>

struct ImageData {
	int width;
	int height;
	int numComp;
};

class Image {
public:
	Image();
	Image(std::filesystem::path filepath, int numReqComp);
	~Image();
	bool writeJpg(std::filesystem::path destFilepath, int quality = 100, const ImageData* imageData = nullptr,
	              const std::vector<unsigned char>& outputData = std::vector<unsigned char>());
	bool writePng(std::filesystem::path destFilepath, const ImageData* imageData = nullptr,
	              const std::vector<unsigned char>& outputData = std::vector<unsigned char>());
	bool resize(unsigned char* inputData, std::vector<unsigned char>& outputData, int out_width,
	            int out_height, int comp);
	void getInfo(std::filesystem::path filepath, int& width, int& height, int& comp) const;

	bool isCorrectLoaded() const;
	unsigned char* getImageData() const;

private:
	unsigned char* m_data;
	std::filesystem::path m_filepath;
	int m_width;
	int m_height;
	int m_numComp;
	const int m_numReqComp;
	bool m_isCorrectLoaded = false;
};

#endif