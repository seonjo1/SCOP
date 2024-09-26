#include "../include/mesh.h"

std::unique_ptr<Mesh> Mesh::createPlane() {
	std::vector<Vertex> vertices = { Vertex{glmath::vec3(0.5f, 0.5f, 0.0f), glmath::vec2(1.0f, 1.0f), glmath::vec3(0.0f, 0.0f, 0.0f)},
								 	 Vertex{glmath::vec3(0.5f, -0.5f, 0.0f), glmath::vec2(1.0f, 0.0f), glmath::vec3(0.0f, 0.0f, 0.0f)},
								 	 Vertex{glmath::vec3(-0.5f, -0.5f, 0.0f), glmath::vec2(0.0f, 0.0f), glmath::vec3(0.0f, 0.0f, 0.0f)},
									 Vertex{glmath::vec3(-0.5f, 0.5f, 0.0f), glmath::vec2(0.0f, 1.0f), glmath::vec3(0.0f, 0.0f, 0.0f)} };

	std::vector<uint32_t> indices = { 0, 3, 1,
									 1, 3, 2 };
									 
	std::unique_ptr<Mesh> mesh(new Mesh());
	mesh->init(vertices, indices);
	return mesh;
}

std::unique_ptr<Mesh> Mesh::createMesh(std::vector<Vertex>& vertices,
										std::vector<uint32_t>& indices, 
										glload::ObjInfo* objInfo) {
	std::unique_ptr<Mesh> mesh(new Mesh());
	mesh->init(vertices, indices);
	mesh->setMaterial(objInfo->marterialInfo);
	return mesh;
}

void Mesh::setVertices(std::vector<Vertex>& vertices) {
	static std::random_device rd;         
	static std::mt19937 g(rd());
	static std::uniform_real_distribution<float> dist(0.0f, 1.0f);

	glmath::vec3 maxV(0.0f);
	glmath::vec3 minV(0.0f);


	for (int i = 0; i < vertices.size(); i++) {
		maxV.x = std::max(maxV.x, vertices[i].pos.x);
		maxV.y = std::max(maxV.y, vertices[i].pos.y);
		maxV.z = std::max(maxV.z, vertices[i].pos.z);
		minV.x = std::min(minV.x, vertices[i].pos.x);
		minV.y = std::min(minV.y, vertices[i].pos.y);
		minV.z = std::min(minV.z, vertices[i].pos.z);

		vertices[i].color = glmath::vec3(dist(g), dist(g), dist(g));
	}

	m_meshPos = (minV + maxV) * 0.5f;
	m_move = glmath::vec3(0.0f);
}

void Mesh::init(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices) {

	setVertices(vertices);

	GLsizei vertexSize = vertices.size();
	m_elementSize = indices.size();

	m_vertexArray = VertexArray::create();
	m_vertexBuffer = Buffer::create(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexSize,
									vertices.data(), GL_STATIC_DRAW);

	m_vertexArray->setAttribute(0, 3, sizeof(Vertex), offsetof(Vertex, pos));
	m_vertexArray->setAttribute(1, 2, sizeof(Vertex), offsetof(Vertex, texCoord));
	m_vertexArray->setAttribute(2, 3, sizeof(Vertex), offsetof(Vertex, color));

	m_elementBuffer = Buffer::create(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * m_elementSize,
									indices.data(), GL_STATIC_DRAW);
}

void Mesh::draw() {
	m_vertexArray->bind();
	glDrawElements(GL_TRIANGLES, m_elementSize, GL_UNSIGNED_INT, 0);
}

void Material::set(glload::Material& materialInfo) {
	for (int i = 0; i < 3; ++i) {
		this->m_Ka[i] = materialInfo.Ka[i];
		this->m_Kd[i] = materialInfo.Kd[i];
		this->m_Ks[i] = materialInfo.Ks[i];
	}

	this->m_Ns = materialInfo.Ns;
	this->m_Ni = materialInfo.Ni;
	this->m_d = materialInfo.d;
	this->m_illum = materialInfo.illum;
}

void Mesh::setMaterial(glload::Material& materialInfo) {
	this->m_material.set(materialInfo);
}

glmath::mat4 Mesh::getViewModelMatrix(glmath::vec3& cameraPos, glmath::vec3& cameraUp, glmath::vec3& cameraFront) {
	glmath::mat4 model = glmath::translate(glmath::mat4(1.0f), m_meshPos + m_move) *
						 glmath::rotate(glmath::mat4(1.0f), glmath::radians(m_degree), glmath::vec3(0.0f, 1.0f, 0.0f)) *
						 glmath::scale(glmath::mat4(1.0f), glmath::vec3(1.0f)) *
						 glmath::translate(glmath::mat4(1.0f), -1 * m_meshPos);
						 
	glmath::mat4 view = glmath::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	return view * model;
}

void Mesh::updateMesh(glmath::vec3& move, float degree) {
	m_move = m_move + move;
	m_degree = m_degree + degree;
	if (m_degree > 360.0f) m_degree -= 360.0f;
}
