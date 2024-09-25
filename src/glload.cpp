#include "../include/glload.h"

void glload::flipImageVertically(int h, int w, int bpp, uint8_t* data) {
	int rowSize = w * (bpp / 8);
	std::vector<uint8_t> tmp(rowSize);
	for (int i = 0; i < h / 2; i++) {
		uint8_t* upperRow = &data[i * rowSize];
		uint8_t* lowerRow = &data[((h - 1) - i) * rowSize];
		std::copy(upperRow, upperRow + rowSize, tmp.begin());
		std::copy(lowerRow, lowerRow + rowSize, upperRow);
		std::copy(tmp.begin(), tmp.end(), lowerRow);
	}
}

bool glload::checkFileExtension(std::string fileName, const std::string extension) {

	int length = fileName.size();
	
	if (length < extension.size()) {
		return false;
	}
	
	std::string fileExt = fileName.substr(length - 4);
	std::transform(fileExt.begin(), fileExt.end(), fileExt.begin(), ::tolower);
	
	return fileExt == extension;
}

bool glload::getBmpInfo(char* fileHeader, bmpInfo& info) {

	info.imgOffBits = *reinterpret_cast<uint32_t*>(&fileHeader[10]);
	info.imgSize = *reinterpret_cast<uint32_t*>(&fileHeader[34]);
	info.imgWidth = *reinterpret_cast<int32_t*>(&fileHeader[18]);
	info.imgHeight = *reinterpret_cast<int32_t*>(&fileHeader[22]);
	info.imgBitCount = *reinterpret_cast<uint16_t*>(&fileHeader[28]);
	info.imgCompression = *reinterpret_cast<uint32_t*>(&fileHeader[30]);

	if (info.imgCompression) {
		std::cerr << "this bmp file is compressed" << std::endl;
		return false;
	}

	if (info.imgBitCount <= 8) {
		std::cerr << "Palette-based BMP files are not supported." << std::endl;
		return false;
	}

	if (!info.imgSize) {
		info.imgSize = std::abs(info.imgWidth * info.imgHeight * (info.imgBitCount / 8));
	}
	return true;
}


std::unique_ptr<uint8_t[]> glload::loadBmpImg(const char* fileName, int* width, int* height, int* channelCount) {

	if (!checkFileExtension(fileName, ".bmp")) {
		std::cerr << "this file is not bmp file" << std::endl;
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

	bmpInfo info;
	if (!getBmpInfo(fileHeader, info)) {
		return nullptr;
	}

    std::unique_ptr<uint8_t[]> data = std::make_unique<uint8_t[]>(info.imgSize);

    fin.seekg(info.imgOffBits, std::ios::beg);
    fin.read(reinterpret_cast<char*>(data.get()), info.imgSize);
	
	if (fin.fail()) {
		std::cerr << "Error: Could not read the BMP image data." << std::endl;
		return nullptr;
	}
	
	if (info.imgHeight < 0) {
		flipImageVertically(-info.imgHeight, info.imgWidth, info.imgBitCount, data.get());
	}

	*width = info.imgWidth;
	*height = std::abs(info.imgHeight);
	*channelCount =  info.imgBitCount / 8;

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

std::unique_ptr<glload::ObjInfo> glload::loadObjFile(const std::string& fileName) {

	if (!checkFileExtension(fileName, ".obj")) {
		std::cerr << "this file is not .obj file" << std::endl;
		return nullptr;
	}

	std::ifstream fin(fileName);
	
	if (!fin.is_open()) {
		std::cerr << fileName << " is not exist" << std::endl;
		return nullptr;
	}

	std::unique_ptr<ObjInfo> objInfo(new ObjInfo());
	std::string line;
	while (std::getline(fin, line)) {
		std::stringstream ss(line);
		std::unique_ptr<IObjLine> objLine = generateLine(ss, fileName);
		if (!objLine) { continue ;}
		if (!objLine->parsingLine(objInfo.get())) { return {}; }
	}

	return objInfo;
}

std::unique_ptr<glload::IObjLine> glload::generateLine(std::stringstream& ss, const std::string& fileName) {
	std::string element;
	ss >> element;
	if (element == "v") return std::unique_ptr<IObjLine>(new VertexLine(ss, fileName));
	else if (element == "mtllib") return std::unique_ptr<IObjLine>(new MaterialLine(ss, fileName)); 
	else if (element == "f") return std::unique_ptr<IObjLine>(new FaceLine(ss, fileName));
	else return nullptr;
}

glload::VertexLine::VertexLine(std::stringstream& ss,  const std::string& fileName)
	: ss(ss) {};

glload::MaterialLine::MaterialLine(std::stringstream& ss,  const std::string& fileName)
	: ss(ss), fileName(fileName) {}

glload::FaceLine::FaceLine(std::stringstream& ss,  const std::string& fileName)
	: ss(ss) {};

bool glload::VertexLine::parsingLine(ObjInfo* objInfo) {
	std::vector<float> v;
	float value;
	
	while (this->ss >> value) {
		v.push_back(value);
	}
	
	if (v.size() != 3) return false;

	objInfo->vertexInfo.vPosInfo.push_back(Pos(v[0], v[1], v[2]));
	return true;
}

std::string glload::MaterialLine::getMtlFilePath(const std::string& mtlFileName) {
	std::string prefix = "";
	std::size_t pos = fileName.rfind('/');
	if (pos != std::string::npos) {
		prefix = fileName.substr(0, pos + 1);
	}
	return prefix + mtlFileName;
}


bool glload::MaterialLine::parsingLine(ObjInfo* objInfo) {

	std::string mtlFileName;
	if (!(ss >> mtlFileName)) {
		return false;
	}

	if (!checkFileExtension(mtlFileName, ".mtl")) {
		std::cerr << "this file is not .mtl file" << std::endl;
		return false;
	}


	std::string mtlFilePath = getMtlFilePath(mtlFileName);

	std::ifstream fin(mtlFilePath);
	
	if (!fin.is_open()) {
		return false;
	}

	std::string line, identifier;
	float fVal;
	uint32_t iVal;
	while (std::getline(fin, line)) {
		std::stringstream ss(line);
		if (!(ss >> identifier)) {
			continue ;
		}
		if (identifier == "Ka") {
			for (int i = 0; i < 3; i++) {
				if (!(ss >> fVal)) return false;
				objInfo->marterialInfo.Ka[i] = fVal;
			}
		} else if (identifier == "Kd") {
			for (int i = 0; i < 3; i++) {
				if (!(ss >> fVal)) return false;
				objInfo->marterialInfo.Kd[i] = fVal;
			}
		} else if (identifier == "Ks") {
			for (int i = 0; i < 3; i++) {
				if (!(ss >> fVal)) return false;
				objInfo->marterialInfo.Ks[i] = fVal;
			}
		} else if (identifier == "Ns") {
			if (!(ss >> fVal)) return false;
			objInfo->marterialInfo.Ns = fVal;
		} else if (identifier == "Ni") {
			if (!(ss >> fVal)) return false;
			objInfo->marterialInfo.Ni = fVal;
		} else if (identifier == "d") {
			if (!(ss >> fVal)) return false;
			objInfo->marterialInfo.d = fVal;
		} else if (identifier == "illum") {
			if (!(ss >> iVal)) return false;
			objInfo->marterialInfo.illum = iVal;
		}
	}
	return true;
}

bool glload::FaceLine::parsingLine(ObjInfo* objInfo) {
	std::vector<uint32_t> v;
	uint32_t value;
	
	while (this->ss >> value) {
		v.push_back(value);
	}
	
	if (v.size() < 3) return false;

	for (int i = 2; i < v.size(); i++) {
		objInfo->indexInfo.faces.push_back(Face(v[0] - 1, v[i - 1] - 1, v[i] - 1));
	}
	return true;
}
