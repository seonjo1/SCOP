#ifndef VERTEXARRAY_H
# define VERTEXARRAY_H

# include "scop.h"

class VertexArray {
public:
	static std::unique_ptr<VertexArray> create();
	~VertexArray();
	void bind();
	uint32_t get();

private:
	VertexArray() {};
	bool genVao();

	uint32_t m_vao{0};
};

#endif