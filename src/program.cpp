#include "../include/program.h"

std::unique_ptr<Program> Program::create(const std::string vsFileName, const std::string fsFileName) {
	std::unique_ptr<Program> program(new Program);
	std::shared_ptr<Shader> vsShader = Shader::create(vsFileName, GL_VERTEX_SHADER);
	std::shared_ptr<Shader> fsShader = Shader::create(fsFileName, GL_FRAGMENT_SHADER);
	if (!program->link({vsShader, fsShader})) {
		return nullptr;
	}

	return program;
}

Program::~Program() {
	if (m_program) {
		glDeleteProgram(m_program);
	}
}

bool Program::link(const std::vector<std::shared_ptr<Shader>>& shaders){

	m_program = glCreateProgram();

	for (const std::shared_ptr<Shader>& shader : shaders) {
		if (!shader) {
			std::cerr << "failed to load shader file" << std::endl;
			return false;
		}
		shader->attachShaderToProgram(m_program);
	}

	glLinkProgram(m_program);
	
	int success = 0;
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[1024];
		glGetProgramInfoLog(m_program, 1024, nullptr, infoLog);
		std::cerr << "failed to link program: " << infoLog << std::endl;
		return false;
	}

	return true;
}

void Program::useProgram() {
	glUseProgram(m_program);
}

void Program::setUniform(const char* varName, GLint value) {
	GLuint location = glGetUniformLocation(m_program, varName);
	glUniform1i(location, value);
}

void Program::setUniform(const char* varName, GLfloat value) {
    GLuint location = glGetUniformLocation(m_program, varName);
    glUniform1f(location, value);
}

void Program::setUniform(const char* varName, glmath::mat4& matrix) {
	GLuint location = glGetUniformLocation(m_program, varName);
	glUniformMatrix4fv(location, 1, GL_FALSE, glmath::value_ptr(matrix));
}