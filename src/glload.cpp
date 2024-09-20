#include "../include/glload.h"

std::unique_ptr<uint8_t[]> glload::loadBmpImg(char* const fileName, int* width, int* height, int* channelCount) {
	std::ifstream fin;
	fin.open(fileName, std::ios::binary);
	if (!fin.is_open()) throw std::runtime_error("Could not open BMP file.");

	glload::BMPFileHeader fileHeader;
    fin.read(reinterpret_cast<char*>(&fileHeader), sizeof(fileHeader));

	// 유효한 BMP 파일인지 확인
    if (fileHeader.bfType != 0x4D42) {
        throw std::runtime_error("Not a valid BMP file.");
    }

	glload::BMPInfoHeader bmpInfo;
    fin.read(reinterpret_cast<char*>(&bmpInfo), sizeof(bmpInfo));

    // 데이터 할당
    std::unique_ptr<uint8_t[]> data = std::make_unique<uint8_t[]>(bmpInfo.biSizeImage);

	// 데이터 옮기기
    fin.seekg(fileHeader.bfOffBits, std::ios::beg);
    fin.read(reinterpret_cast<char*>(data.get()), bmpInfo.biSizeImage);
	*width = bmpInfo.biWidth;
	*height = bmpInfo.biHeight;
	*channelCount =  bmpInfo.biBitCount / 8;
    
	fin.close();

    return data;
}
