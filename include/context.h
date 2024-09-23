#ifndef CONTEXT_H
# define CONTEXT_H

# include "scop.h"

class Context {
public:
	static std::unique_ptr<Context> Create();
	void Render();
	void Reshape(int width, int height);
	~Context();

private:
	Context() {};
	bool init();

	int m_width {WINDOW_WIDTH};
	int m_height {WINDOW_HEIGHT};
	
	uint32_t m_vao{0};
	uint32_t m_vbo{0};
	uint32_t m_ebo{0};

	uint32_t m_vertexShader{0};
	uint32_t m_fragmentShader{0};
	uint32_t m_program{0};

	uint32_t m_texture{0};
	std::unique_ptr<uint8_t[]> m_image;
	int m_texWidth{0};
	int m_texHeight{0};
	int m_texChannelCount{0};
};

#endif