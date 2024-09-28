#ifndef GLLOAD_H
# define GLLOAD_H

# include <cstdint>
# include <iostream>
# include <fstream>
# include <sstream>
# include <memory>
# include <optional>
# include <algorithm>
# include <vector>
# include <cmath>

namespace glload {

struct bmpInfo {
	uint32_t imgOffBits;
	uint32_t imgSize;
	int32_t imgWidth;
	int32_t imgHeight;
	uint16_t imgBitCount;
	uint32_t imgCompression;
};

struct Pos {
	float x;
	float y;
	float z;
	
	Pos(float x, float y, float z) : x(x), y(y), z(z) {};
};

struct Normal {
	float x;
	float y;
	float z;

	Normal(float x, float y, float z) : x(x), y(y), z(z) {};
};

struct TexCoord {
	float x;
	float y;

	TexCoord(float x, float y) : x(x), y(y) {};
};

struct VertexInfo {
	std::vector<Pos> vPosInfo; 
	std::vector<TexCoord> vTexInfo;
	std::vector<Normal> vNormalInfo;
};

struct Face {
	int32_t posIdx[3];
	int32_t texIdx[3];
	int32_t normalIdx[3];
	int32_t mi;
	bool hasTexture {true};
	bool hasNormal {true};
};

struct IndexInfo {
	std::vector<Face> faces;
};

struct Material {
	std::string name;
	float Ka[3] { 0.2f, 0.2f, 0.2f };
	float Kd[3] { 0.8f, 0.8f, 0.8f };
	float Ks[3] { 0.5f, 0.5f, 0.5f };
	float Ns { 50.0f };
	float Ni { 1.0f };
	float d { 1.0f };
	uint32_t illum { 2 };
};


struct MaterialInfo {
	std::vector<Material> materials;
	int32_t materialIdx{-1};
};

struct ObjInfo {
	VertexInfo vertexInfo;
	IndexInfo indexInfo;
	MaterialInfo marterialInfo;
};

class IObjLine {
public:
	virtual ~IObjLine() = default;
	virtual bool parsingLine(ObjInfo* objInfo) = 0;
};

class VertexLine : public IObjLine {
public:
	VertexLine(std::stringstream& ss);
	virtual ~VertexLine() = default;
	virtual bool parsingLine(ObjInfo* objInfo) override;

private:
	std::stringstream& ss;
};

class VertexTextureLine : public IObjLine {
public:
	VertexTextureLine(std::stringstream& ss);
	virtual ~VertexTextureLine() = default;
	virtual bool parsingLine(ObjInfo* objInfo) override;

private:
	std::stringstream& ss;
};

class VertexNormalLine : public IObjLine {
public:
	VertexNormalLine(std::stringstream& ss);
	virtual ~VertexNormalLine() = default;
	virtual bool parsingLine(ObjInfo* objInfo) override;

private:
	std::stringstream& ss;
};

class MaterialLine : public IObjLine {
public:
	MaterialLine(std::stringstream& ss, const std::string& fileName);
	virtual ~MaterialLine() = default;
	virtual bool parsingLine(ObjInfo* objInfo) override;

private:
	std::string getMtlFilePath(const std::string& mtlFileName);

	std::stringstream& ss;
	std::string fileName;
};

class FaceLine : public IObjLine {
public:
	FaceLine(std::stringstream& ss);
	virtual ~FaceLine() = default;
	virtual bool parsingLine(ObjInfo* objInfo) override;

private:
	std::stringstream& ss;
};

class ChangeMaterialLine : public IObjLine {
public:
	ChangeMaterialLine(std::stringstream& ss);
	virtual ~ChangeMaterialLine() = default;
	virtual bool parsingLine(ObjInfo* objInfo) override;

private:
	std::stringstream& ss;
};

void flipImageVertically(int h, int w, int bpp, uint8_t* data);
bool getBmpInfo(char* fileHeader, bmpInfo& info);
bool checkFileExtension(std::string fileName, const std::string extension);
Face makeFace(std::vector<std::vector<int32_t>>& faceVec, int32_t mi, int i);
std::string slashTospace(const std::string& str);
std::optional<std::string> loadShaderFile(const std::string& fileName);
std::unique_ptr<ObjInfo> loadObjFile(const std::string& fileName);
std::unique_ptr<IObjLine> generateLine(std::stringstream& ss, const std::string& fileName);
std::unique_ptr<uint8_t[]> loadBmpImg(const char* fileName, int* width, int* height, int* channelCount);
}

#endif