#ifndef MESH_H
# define MESH_H

# include "scop.h"
# include "vertexArray.h"
# include "buffer.h"

struct Vertex {
	glmath::vec3 pos;
	glmath::vec2 texCoord;
};

class Mesh {
public:
	static std::unique_ptr<Mesh> createPlane();
	void draw();

private:
	Mesh() {};
	void create(std::vector<Vertex>& vertices, std::vector<uint32_t>& indices);

	std::unique_ptr<VertexArray> m_vertexArray;
	std::shared_ptr<Buffer> m_vertexBuffer; 
	std::shared_ptr<Buffer> m_elementBuffer;
	GLsizei m_elementSize;
};

#endif