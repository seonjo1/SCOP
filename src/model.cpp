#include "../include/model.h"

std::unique_ptr<Model> Model::create(std::string fileName) {
	std::unique_ptr<Model> model(new Model());
	if (!model->createMeshes(fileName)) {
		return nullptr;
	}
	return model;
}

void Model::addVertex(glload::ObjInfo* objInfo, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, uint32_t idx) {
	vertices.push_back(Vertex{glmath::vec3(objInfo->vertexInfo.vPosInfo[idx].x,
										objInfo->vertexInfo.vPosInfo[idx].y,
										objInfo->vertexInfo.vPosInfo[idx].z),
							glmath::vec2(objInfo->vertexInfo.vTexInfo[idx].x,
										objInfo->vertexInfo.vTexInfo[idx].y),
							glmath::vec3(0.0f)});
	indices.push_back(vertices.size() - 1);
}

bool Model::createMeshes(const std::string& fileName) {
	std::unique_ptr<glload::ObjInfo> objInfo = glload::loadObjFile(fileName);
	if (!objInfo) {
		std::cerr << fileName << " is invalid .obj file" << std::endl;
		return false;
	}

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;

	for (int i = 0; i < objInfo->indexInfo.faces.size(); i++) {
		addVertex(objInfo.get(), vertices, indices, objInfo->indexInfo.faces[i].i1);
		addVertex(objInfo.get(), vertices, indices, objInfo->indexInfo.faces[i].i2);
		addVertex(objInfo.get(), vertices, indices, objInfo->indexInfo.faces[i].i3);
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