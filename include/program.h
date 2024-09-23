#ifndef PROGRAM_H
# define PROGRAM_H

# include "scop.h"
# include "shader.h"

class Program {
public:
	static std::unique_ptr<Program> create(const std::string vsFileName, const std::string fsFileName);
	~Program();
	uint32_t get();
private:
	Program() {};
	bool link(const std::vector<std::shared_ptr<Shader>>& shaders);
	uint32_t m_program{0};
};

#endif