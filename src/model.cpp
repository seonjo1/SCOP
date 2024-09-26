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

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	for (int i = 0; i < objInfo->vertexInfo.vPosInfo.size(); i++) {
		vertices.push_back(Vertex{glmath::vec3(objInfo->vertexInfo.vPosInfo[i].x,
						   					   objInfo->vertexInfo.vPosInfo[i].y,
						   					   objInfo->vertexInfo.vPosInfo[i].z),
								  glmath::vec2(objInfo->vertexInfo.vTexInfo[i].x,
								  			   objInfo->vertexInfo.vTexInfo[i].y),
								  glmath::vec3(objInfo->vertexInfo.vColorInfo[i].r,
						   					   objInfo->vertexInfo.vColorInfo[i].g,
						   					   objInfo->vertexInfo.vColorInfo[i].b)});
	}

	for (int j = 0; j < objInfo->indexInfo.faces.size(); j++) {
		indices.push_back(objInfo->indexInfo.faces[j].i1);
		indices.push_back(objInfo->indexInfo.faces[j].i2);
		indices.push_back(objInfo->indexInfo.faces[j].i3);
	}
	
	m_meshes.push_back(Mesh::createMesh(vertices, indices, objInfo.get()));

	return true;
}

void Model::draw(Program* program, glmath::vec3& cameraPos, glmath::vec3& cameraUp, glmath::vec3& cameraFront) {
	for (std::unique_ptr<Mesh>& mesh : m_meshes) {		
		glmath::mat4 viewModelMatrix = mesh->getViewModelMatrix(cameraPos, cameraUp, cameraFront);
		program->setUniform("viewModel", viewModelMatrix);
		mesh->draw();
	}
}

void Model::updateModel(glmath::vec3& move, float degree) {
	for (std::unique_ptr<Mesh>& mesh : m_meshes) {
		mesh->updateMesh(move, degree);
	}
}