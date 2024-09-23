#ifndef CONTEXT_H
# define CONTEXT_H

# include "scop.h"
# include "vertexArray.h"
# include "buffer.h"
# include "Shader.h"

class Context {
public:
	static std::unique_ptr<Context> create();
	void Render();
	void Reshape(int width, int height);
	~Context();

private:
	Context() {};
	bool init();

	int m_width {WINDOW_WIDTH};
	int m_height {WINDOW_HEIGHT};
	

	std::unique_ptr<VertexArray> m_vertexArray;
	std::shared_ptr<Buffer> m_vertexBuffer; 
	std::shared_ptr<Buffer> m_elementBuffer; 
	std::unique_ptr<Shader> m_vertexShader;
	std::unique_ptr<Shader> m_fragmentShader;

	uint32_t m_program{0};
	uint32_t m_texture{0};
	std::unique_ptr<uint8_t[]> m_image;
	int m_texWidth{0};
	int m_texHeight{0};
	int m_texChannelCount{0};
};

#endif