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

struct vPos {
	float x;
	float y;
	float z;
};

struct vNormal {
	float x;
	float y;
	float z;
};

struct vTexCoord {
	float x;
	float y;
};

struct VertexInfo {
	std::vector<vPos> vPosInfo; 
	// std::vector<vNormal> vNormalInfo; 
	// std::vector<vTexCoord> vTexInfo; 
};

struct iFace {
	std::vector<uint32_t> indexVec;
};

struct IndexInfo {
	std::vector<iFace> faces;
};

struct ObjInfo {
	VertexInfo vertexInfo;
	IndexInfo indexInfo;
};

bool isBmpFile(std::string fileName);
std::unique_ptr<uint8_t[]> loadBmpImg(const char* fileName, int* width, int* height, int* channelCount);
std::optional<std::string> loadShaderFile(const std::string& fileName);
ObjInfo loadObjFile(const std::string& fileName);

}

#endif