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