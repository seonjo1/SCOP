#include "../include/glload.h"

bool glload::isBmpFile(std::string fileName) {

	int length = fileName.size();
	
	if (length < 4) {
		return false;
	}
	
	std::string ext = fileName.substr(length - 4);
	std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
	
	return ext == ".bmp";
}

std::unique_ptr<uint8_t[]> glload::loadBmpImg(const char* fileName, int* width, int* height, int* channelCount) {

	if (!isBmpFile(fileName)) {
		std::cerr << "this file is not bmp format" << std::endl;
		return nullptr;
	}

	std::ifstream fin(fileName, std::ios::binary);
	if (!fin.is_open()) {
		std::cerr << fileName << " is not exist" << std::endl;
		return nullptr;
	}
	
	char fileHeader[54];
    fin.read(fileHeader, 54);

    if (*reinterpret_cast<uint16_t*>(&fileHeader[0]) != 0x4D42) {
		std::cerr << fileName << " is invalid bmp file" << std::endl;
        return nullptr;
    }

	uint32_t imgOffBits = *reinterpret_cast<uint32_t*>(&fileHeader[10]);
	uint32_t imgSize = *reinterpret_cast<uint32_t*>(&fileHeader[34]);
	int32_t imgWidth = *reinterpret_cast<int32_t*>(&fileHeader[18]);
	int32_t imgHeight = *reinterpret_cast<int32_t*>(&fileHeader[22]);
	uint16_t imgBitCount = *reinterpret_cast<uint16_t*>(&fileHeader[28]);
	uint32_t imgCompression = *reinterpret_cast<uint32_t*>(&fileHeader[30]);

	if (imgCompression) {
		std::cerr << "this bmp file is compressed" << std::endl;
		return nullptr;
	}

	if (imgBitCount <= 8) {
		std::cerr << "Palette-based BMP files are not supported." << std::endl;
		return nullptr;
	}

	if (!imgSize) {
		imgSize = std::abs(imgWidth * imgHeight * (imgBitCount / 8));
	}

    std::unique_ptr<uint8_t[]> data = std::make_unique<uint8_t[]>(imgSize);

    fin.seekg(imgOffBits, std::ios::beg);
    fin.read(reinterpret_cast<char*>(data.get()), imgSize);
	
	if (fin.fail()) {
		std::cerr << "Error: Could not read the BMP image data." << std::endl;
		return nullptr;
	}
	
	if (imgHeight < 0) {
		imgHeight = -imgHeight;
		int rowSize = imgWidth * (imgBitCount / 8);
		std::vector<uint8_t> tmp(rowSize);
		for (int i = 0; i < imgHeight / 2; i++) {
			uint8_t* upperRow = &data[i * rowSize];
			uint8_t* lowerRow = &data[((imgHeight - 1) - i) * rowSize];
			std::copy(upperRow, upperRow + rowSize, tmp.begin());
			std::copy(lowerRow, lowerRow + rowSize, upperRow);
			std::copy(tmp.begin(), tmp.end(), lowerRow);
		}
	}

	*width = imgWidth;
	*height = imgHeight;
	*channelCount =  imgBitCount / 8;

	fin.close();

    return data;
}

std::optional<std::string> glload::loadShaderFile(const std::string& fileName) {

	std::ifstream fin(fileName);
	
	if (!fin.is_open()) {
		std::cout << "failed to open shader file: " << fileName << std::endl;
		return {};
	}
	
	std::stringstream code;
	code << fin.rdbuf();
	fin.close();

	return code.str();
}

glload::ObjInfo glload::loadObjFile(const std::string& fileName) {
	
}