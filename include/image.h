#ifndef IMAGE_H
# define IMAGE_H

# include "scop.h"

class Image {
public:
	static std::shared_ptr<Image> create(const char* fileName);

private:
	bool load(const char* fileName);

	std::unique_ptr<uint8_t[]> m_image;
	int m_width;
	int m_height;
	int m_channelCount;
};

#endif