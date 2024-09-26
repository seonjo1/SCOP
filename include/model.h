#ifndef MODEL_H
# define MODEL_H

# include "scop.h"
# include "mesh.h"
# include "program.h"

class Model {
public:
	static std::unique_ptr<Model> create(std::string fileName);
	void draw(Program* program, glmath::vec3& cameraPos, glmath::vec3& cameraUp, glmath::vec3& cameraFront);
	void updateModel(glmath::vec3& move, float degree);

private:
	bool createMeshes(const std::string& fileName);
	void addVertex(glload::ObjInfo* objInfo, std::vector<Vertex>& vertices, std::vector<uint32_t>& indices, uint32_t idx);

	std::vector<std::unique_ptr<Mesh>> m_meshes;
};

#endif