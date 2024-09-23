#ifndef VERTEXARRAY_H
# define VERTEXARRAY_H

# include "scop.h"

class VertexArray {
public:
	static std::unique_ptr<VertexArray> create();
	~VertexArray();
	void bind();
	void setAttribute(GLuint index, GLint size, GLsizei stride, size_t pointer);

private:
	VertexArray() {};
	void genVao();

	uint32_t m_vao{0};
};

#endif