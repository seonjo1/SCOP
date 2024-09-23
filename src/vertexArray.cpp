#include "../include/vertexArray.h"

std::unique_ptr<VertexArray> VertexArray::create() {
	std::unique_ptr<VertexArray> vertexArray(new VertexArray());
	if (vertexArray->genVao()) {
		return nullptr;
	}
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

bool VertexArray::genVao() {
	glGenVertexArrays(1, &m_vao);
	bind();
}

uint32_t VertexArray::get() {
	return m_vao;
}
