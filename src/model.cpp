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

void Model::setModelPos(std::vector<Vertex>& vertices) {
    glmath::vec3 maxV(-std::numeric_limits<float>::infinity());
    glmath::vec3 minV(std::numeric_limits<float>::infinity());

	for (int i = 0; i < vertices.size(); i++) {
		maxV.x = std::max(maxV.x, vertices[i].pos.x);
		maxV.y = std::max(maxV.y, vertices[i].pos.y);
		maxV.z = std::max(maxV.z, vertices[i].pos.z);
		minV.x = std::min(minV.x, vertices[i].pos.x);
		minV.y = std::min(minV.y, vertices[i].pos.y);
		minV.z = std::min(minV.z, vertices[i].pos.z);
	}

	m_modelPos = (minV + maxV) * 0.5f;
	m_move = glmath::vec3(0.0f);
}

void Model::setColor(std::vector<Vertex>& vertices) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<float> dis(0.0f, 1.0f);
	
	for (int i = 0; i < vertices.size() / 3; i++) {
		glmath::vec3 color(dis(gen), dis(gen), dis(gen));
		vertices[3 * i].color = color;
		vertices[3 * i + 1].color = color;
		vertices[3 * i + 2].color = color;
	}
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
	
	setModelPos(vertices);
	setColor(vertices);

	m_meshes.push_back(Mesh::createMesh(vertices, indices, objInfo.get()));

	return true;
}

void Model::draw(Program* program, glmath::vec3& cameraPos, glmath::vec3& cameraUp, glmath::vec3& cameraFront) {
	glmath::mat4 model = glmath::translate(glmath::mat4(1.0f), m_move) *
						 glmath::rotate(glmath::mat4(1.0f), glmath::radians(m_degree), glmath::vec3(0.0f, 1.0f, 0.0f)) *
						 glmath::scale(glmath::mat4(1.0f), glmath::vec3(1.0f)) *
						 glmath::translate(glmath::mat4(1.0f), -1 * m_modelPos);
						 
	glmath::mat4 view = glmath::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	glmath::mat4 viewModelMatrix = view * model;
	program->setUniform("viewModel", viewModelMatrix);
	program->setUniform("texRatio", m_texRatio);
	for (std::unique_ptr<Mesh>& mesh : m_meshes) {		
		mesh->draw();
	}
}

void Model::updateModel(glmath::vec3& move, float degree, float transSpeed) {
	m_move = m_move + move;
	m_degree = m_degree + degree;
	if (m_degree > 360.0f) { m_degree -= 360.0f; }
	m_texRatio = std::clamp(m_texRatio + transSpeed, 0.0f, 1.0f);
}