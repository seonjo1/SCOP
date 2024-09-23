#include "../include/buffer.h"

std::shared_ptr<Buffer> Buffer::create(GLenum type, GLsizeiptr size,
										const void* data, GLenum usage) {
	std::shared_ptr<Buffer> buffer(new Buffer());
	buffer->genBuffer(type, size, data, usage);

	return buffer;
}

Buffer::~Buffer() {
	if (m_buffer) {
		glDeleteBuffers(1, &m_buffer);
	}
}

void Buffer::genBuffer(GLenum type, GLsizeiptr size,
						const void* data, GLenum usage) {
	glGenBuffers(1, &m_buffer);
	glBindBuffer(type, m_buffer);
	glBufferData(type, size, data, usage);
}