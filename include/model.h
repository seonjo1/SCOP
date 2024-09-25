#ifndef MODEL_H
# define MODEL_H

# include "scop.h"
# include "mesh.h"

class Model {
public:
	static std::unique_ptr<Model> create(std::string fileName);
private:
	bool createMeshes(const std::string& fileName);

	std::vector<Mesh> meshes;
};

#endif