#ifndef TEXTURE_H
# define TEXTURE_H

# include "scop.h"
# include "image.h"

class Texture {
public:
	static std::unique_ptr<Texture> create(std::shared_ptr<Image> image);
	~Texture();
	void activeTexture(GLenum texUnit);

private:
	Texture() {};
	void genTexture(std::shared_ptr<Image> image);
	void bind();
	void setParam();

	uint32_t m_texture;

};

#endif