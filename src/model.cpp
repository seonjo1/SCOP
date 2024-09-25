#include "../include/model.h"

std::unique_ptr<Model> Model::create(std::string fileName) {
	std::unique_ptr<Model> model(new Model());
	if (!model->createMeshes(fileName)) {
		return nullptr;
	}
	return model;
}

bool Model::createMeshes(const std::string& fileName) {
	std::unique_ptr<glload::ObjInfo> objInfo = glload::loadObjFile(fileName);
	if (!objInfo) {
		std::cerr << fileName << " is invalid .obj file" << std::endl;
		return false;
	}
	
	std::cout << "vertex info\n";
	for (int i = 0; i < objInfo->vertexInfo.vPosInfo.size(); i++) {
		std::cout << "x: " << objInfo->vertexInfo.vPosInfo[i].x << " ";
		std::cout << "y: " << objInfo->vertexInfo.vPosInfo[i].y << " ";
		std::cout << "z: " << objInfo->vertexInfo.vPosInfo[i].z << "\n";
	}
	std::cout << "\nindex info\n";
	for (int j = 0; j < objInfo->indexInfo.faces.size(); j++) {
		std::cout << "index 1: " << objInfo->indexInfo.faces[j].index[0] << " ";
		std::cout << "index 2: " << objInfo->indexInfo.faces[j].index[1] << " ";
		std::cout << "index 3: " << objInfo->indexInfo.faces[j].index[2] << "\n";
	}
	std::cout << "\nmaterial info\n";
	std::cout << "Ka.x: " << objInfo->marterialInfo.Ka[0] << "\n";
	std::cout << "Ka.y: " << objInfo->marterialInfo.Ka[1] << "\n";
	std::cout << "Ka.z: " << objInfo->marterialInfo.Ka[2] << "\n";
	std::cout << "Kd.x: " << objInfo->marterialInfo.Kd[0] << "\n";
	std::cout << "Kd.y: " << objInfo->marterialInfo.Kd[1] << "\n";
	std::cout << "Kd.z: " << objInfo->marterialInfo.Kd[2] << "\n";
	std::cout << "Ks.x: " << objInfo->marterialInfo.Ks[0] << "\n";
	std::cout << "Ks.y: " << objInfo->marterialInfo.Ks[1] << "\n";
	std::cout << "Ks.z: " << objInfo->marterialInfo.Ks[2] << "\n";
	std::cout << "Ns: " << objInfo->marterialInfo.Ns << "\n";
	std::cout << "Ni: " << objInfo->marterialInfo.Ni << "\n";
	std::cout << "d: " << objInfo->marterialInfo.d << "\n";
	std::cout << "illum: " << objInfo->marterialInfo.illum << "\n";
	return true;
}
