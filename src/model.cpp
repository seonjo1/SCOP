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
								  glmath::vec2(0.0f, 0.0f)});
	}

	for (int j = 0; j < objInfo->indexInfo.faces.size(); j++) {
		indices.push_back(objInfo->indexInfo.faces[j].index[0]);
		indices.push_back(objInfo->indexInfo.faces[j].index[1]);
		indices.push_back(objInfo->indexInfo.faces[j].index[2]);
	}

	m_meshes.push_back(Mesh::createMesh(vertices, indices, objInfo.get()));
	
	return true;
}

void Model::draw(Program* program, glmath::vec3& cameraPos, glmath::vec3& cameraUp) {
	for (std::unique_ptr<Mesh>& mesh : m_meshes) {		
		glmath::mat4 viewModelMatrix = mesh->getViewModelMatrix(cameraPos, cameraUp);
		program->setUniform("viewModel", viewModelMatrix);
		mesh->draw();
	}
}
