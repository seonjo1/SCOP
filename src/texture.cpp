#include "../include/texture.h"

std::unique_ptr<Texture> Texture::create(std::shared_ptr<Image> image) {
	std::unique_ptr<Texture> texture(new Texture());
	texture->genTexture(image);
	return texture;
}

void Texture::bind() {
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

void Texture::setParam() {
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

void Texture::genTexture(std::shared_ptr<Image> image) {

	glGenTextures(1, &m_texture);
	bind();
	setParam();
	image->loadTexImageToGPU();
	glGenerateMipmap(GL_TEXTURE_2D);
}

Texture::~Texture() {
	if (m_texture) {
		glDeleteTextures(1, &m_texture);
	}
}

void Texture::activeTexture(GLenum texUnit) {
	glActiveTexture(texUnit);
	bind();
}
