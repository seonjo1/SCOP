#include "../include/image.h"

std::shared_ptr<Image> Image::create(const char* fileName) {
	std::shared_ptr<Image> image(new Image());
	if (!image->load(fileName)) {
		return nullptr;
	}
	return image;
}

bool Image::load(const char* fileName) {
	m_image = glload::loadBmpImg("./image/sample.bmp", &m_width, &m_height, &m_channelCount);
	if (!m_image) {
		return false;
	}
	return true;
}

void Image::loadTexImageToGPU() {

	GLenum format = GL_BGRA;
	
	switch (m_channelCount) {
		default: break;
		case 2: format = GL_RG; break;
		case 3: format = GL_BGR; break;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height,
					0, format, GL_UNSIGNED_BYTE, m_image.get());
}
