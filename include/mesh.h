#ifndef MESH_H
# define MESH_H

# include "scop.h"
# include "vertexArray.h"
# include "buffer.h"
# include <random>

struct Vertex {
	glmath::vec3 pos;
	glmath::vec2 texCoord;
	glmath::vec3 color;
};

class Material {
public:
	Material() = default;
	void setMaterial(glload::Material& materialInfo);

private:
	float m_Ka[3] { 0.2f, 0.2f, 0.2f };
	float m_Kd[3] { 0.8f, 0.8f, 0.8f };
	float m_Ks[3] { 0.5f, 0.5f, 0.5f };
	float m_Ns { 50.0f };
	float m_Ni { 1.0f };
	float m_d { 1.0f };
	uint32_t m_illum { 2 };
};

class Mesh {
public:
	static std::unique_ptr<Mesh> createPlane();
	static std::unique_ptr<Mesh> createMesh(std::vector<Vertex>& vertices,
											std::vector<uint32_t>& indices, 
											glload::ObjInfo* objInfo);
	void draw();

private:
	Mesh() = default;
	void init(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);
	void initMaterial(glload::Material& materialInfo);

	std::unique_ptr<VertexArray> m_vertexArray;
	std::shared_ptr<Buffer> m_vertexBuffer; 
	std::shared_ptr<Buffer> m_elementBuffer;
	GLsizei m_elementSize;
	Material m_material;
};

#endif