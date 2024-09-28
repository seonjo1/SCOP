#ifndef MODEL_H
# define MODEL_H

# include "scop.h"
# include "mesh.h"
# include "program.h"
# include <cmath>
# include <algorithm>

class Model {
public:
	static std::unique_ptr<Model> create(std::string fileName);
	void draw(Program* program, glmath::vec3& cameraPos, glmath::vec3& cameraUp, glmath::vec3& cameraFront);
	void updateModel(glmath::vec3& move, float degree, float transSpeed);

private:
	bool createMeshes(const std::string& fileName);
	void addVertex(glload::ObjInfo* objInfo, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, glload::Face& face);
	void setColor(std::vector<Vertex>& vertices, std::vector<glmath::vec3>& colors);
	void setModelPos(std::vector<Vertex>& vertices);
	void makeTextureCoord(Vertex& vertex);


	std::vector<std::unique_ptr<Mesh>> m_meshes;
	glmath::vec3 m_modelPos{0.0f, 0.0f, 0.0f};
	glmath::vec3 m_move{0.0f, 0.0f, 0.0f};
	float m_degree{0.0f};
	float m_texRatio{0.0f};
};

#endif