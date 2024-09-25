#include "../include/mesh.h"

std::unique_ptr<Mesh> Mesh::createPlane() {

	std::vector<Vertex> vertices = { Vertex{glmath::vec3(0.5f, 0.5f, 0.0f), glmath::vec2(1.0f, 1.0f)},
								 	 Vertex{glmath::vec3(0.5f, -0.5f, 0.0f), glmath::vec2(1.0f, 0.0f)},
								 	 Vertex{glmath::vec3(-0.5f, -0.5f, 0.0f), glmath::vec2(0.0f, 0.0f)},
									 Vertex{glmath::vec3(-0.5f, 0.5f, 0.0f), glmath::vec2(0.0f, 1.0f)} };

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
	mesh->init(vertices, indices, objInfo);
	return mesh;
}

void Mesh::init(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, glload::ObjInfo* objInfo) {

	GLsizei vertexSize = vertices.size();
	m_elementSize = indices.size();

	m_vertexArray = VertexArray::create();
	m_vertexBuffer = Buffer::create(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexSize,
									vertices.data(), GL_STATIC_DRAW);

	m_vertexArray->setAttribute(0, 3, sizeof(Vertex), offsetof(Vertex, pos));
	m_vertexArray->setAttribute(1, 2, sizeof(Vertex), offsetof(Vertex, texCoord));

	m_elementBuffer = Buffer::create(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * m_elementSize,
									indices.data(), GL_STATIC_DRAW);
}

void Mesh::draw() {
	m_vertexArray->bind();
	glDrawElements(GL_TRIANGLES, m_elementSize, GL_UNSIGNED_INT, 0);
}

Mesh::Mesh(const Material& material) : m_material(material) {};
