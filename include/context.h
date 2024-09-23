#ifndef CONTEXT_H
# define CONTEXT_H

# include "scop.h"
# include "vertexArray.h"
# include "buffer.h"
# include "program.h"
# include "image.h"
# include "texture.h"
# include "mesh.h"

class Context {
public:
	static std::unique_ptr<Context> create();
	void Render();
	void Reshape(int width, int height);

private:
	Context() {};
	bool init();

	int m_width {WINDOW_WIDTH};
	int m_height {WINDOW_HEIGHT};

	std::unique_ptr<Mesh> m_plane;	
	std::unique_ptr<Program> m_program;
	std::shared_ptr<Image> m_image;
	std::unique_ptr<Texture> m_texture;
};

#endif