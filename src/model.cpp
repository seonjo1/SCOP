#include "../include/model.h"

std::unique_ptr<Model> Model::create(std::string fileName) {
	std::unique_ptr<Model> model(new Model());
	if (!model->createMeshes(fileName)) {
		return nullptr;
	}
	return model;
}

bool Model::isAcrossUVBoundary(std::vector<Vertex>& vertices, int idx) {

	bool startAria = false;
	bool endAria = false;

	for (int i = 0; i < 3; i++) {
		if (vertices[idx + i].pos.x <= 0 && vertices[idx + i].pos.z >= 0) {
			startAria = true;
		}
		if (vertices[idx + i].pos.x <= 0 && vertices[idx + i].pos.z < 0) {
			endAria = true;
		}
	}
	return (startAria && endAria);
}

void Model::makeTextureCoord(std::vector<Vertex>& vertices, int idx) {
	float patternNum = 8;
	for (int i = 0; i < 3; i++) {
		glmath::vec3 pos = vertices[idx + i].pos;

		// UV 텍스처 코드
		float r = std::sqrt(pos.x * pos.x + pos.y * pos.y + pos.z * pos.z);
		if (r == 0) r = 0.01f;
		float theta = std::atan2(pos.z, pos.x);
		float phi = std::asin(pos.y / r);
		float U = (phi + glmath::pi / 2) / glmath::pi * patternNum;
		float V = (theta + glmath::pi) / (2 * glmath::pi) * patternNum;
		vertices[idx + i].texCoord.x = V;
		vertices[idx + i].texCoord.y = U;
	}
	if (isAcrossUVBoundary(vertices, idx)) {
		for (int i = 0; i < 3; i++) {
			if (vertices[idx + i].texCoord.x < patternNum / 2) {
				vertices[idx + i].texCoord.x += patternNum;
			}
		}
	}
}

void Model::makeNormalVector(std::vector<Vertex>& vertices, int idx) {
	
	glmath::vec3 v1(vertices[idx + 1].pos - vertices[idx].pos);
	glmath::vec3 v2(vertices[idx + 2].pos - vertices[idx].pos);

	glmath::vec3 normal = glmath::normalize(glmath::cross(v1, v2));

	vertices[idx].normal = normal;
	vertices[idx + 1].normal = normal;
	vertices[idx + 2].normal = normal;
}

void Model::addVertex(glload::ObjInfo* objInfo, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, glload::Face& face) {
	for (int i = 0; i < 3; i++) {
		int32_t posIdx = face.posIdx[i]; 
		int32_t texIdx = face.texIdx[i]; 
		int32_t normalIdx = face.normalIdx[i];
		
		vertices.push_back(Vertex{glmath::vec3(objInfo->vertexInfo.vPosInfo[posIdx].x,
											objInfo->vertexInfo.vPosInfo[posIdx].y,
											objInfo->vertexInfo.vPosInfo[posIdx].z),
								glmath::vec2(face.hasTexture ? objInfo->vertexInfo.vTexInfo[texIdx].x,
														   	   objInfo->vertexInfo.vTexInfo[texIdx].y
															 : glmath::vec2(0.0f)),
								glmath::vec3(face.hasNormal ? objInfo->vertexInfo.vNormalInfo[normalIdx].x,
															  objInfo->vertexInfo.vNormalInfo[normalIdx].y,
															  objInfo->vertexInfo.vNormalInfo[normalIdx].z
															: glmath::vec3(0.0f))});
		indices.push_back(vertices.size() - 1);
	}
	
	if (!face.hasTexture) {
		makeTextureCoord(vertices, vertices.size() - 3);
	}
	
	if (!face.hasNormal) {
		makeNormalVector(vertices, vertices.size() - 3);
	}
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

void Model::setColor(std::vector<Vertex>& vertices, std::vector<glmath::vec3>& colors) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<float> dis(0.0f, 1.0f);
	
	for (int i = 0; i < vertices.size() / 3; i++) {
		glmath::vec3 color(dis(gen), dis(gen), dis(gen));
		colors.push_back(color);
		colors.push_back(color);
		colors.push_back(color);
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
	std::vector<glmath::vec3> colors;

	for (int i = 0; i < objInfo->indexInfo.faces.size(); i++) {
		addVertex(objInfo.get(), vertices, indices, objInfo->indexInfo.faces[i]);
	}
	
	setModelPos(vertices);
	setColor(vertices, colors);

	m_meshes.push_back(Mesh::createMesh(vertices, indices, colors, objInfo.get()));

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