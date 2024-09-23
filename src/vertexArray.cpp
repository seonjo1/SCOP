#include "../include/vertexArray.h"

std::unique_ptr<VertexArray> VertexArray::create() {
	std::unique_ptr<VertexArray> vertexArray(new VertexArray());
	vertexArray->genVao();

	return vertexArray;
}

VertexArray::~VertexArray() {
	if (m_vao) {
		glDeleteVertexArrays(1, &m_vao);
	}
}

void VertexArray::bind() {
	glBindVertexArray(m_vao);
}

void VertexArray::genVao() {
	glGenVertexArrays(1, &m_vao);
	bind();
}

void VertexArray::setAttribute(GLuint index, GLint size,
								GLsizei stride, size_t pointer) {
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const void*>(pointer));
}
