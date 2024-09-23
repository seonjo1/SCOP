#ifndef SHADER_H
# define SHADER_H

# include "scop.h"

class Shader {
public:
	static std::unique_ptr<Shader> create(const std::string& filePath, GLenum type);
	~Shader();
	void attachShaderToProgram(uint32_t program);

private:
	Shader() {};
	bool load(const std::string& filePath, GLenum type);
	uint32_t m_shader{0};
};

#endif