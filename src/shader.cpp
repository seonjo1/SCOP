#include "../include/shader.h"

std::unique_ptr<Shader> Shader::create(const std::string& filePath, GLenum type) {
	std::unique_ptr<Shader> shader(new Shader());
	if (!shader->load(filePath, type)) {
		return nullptr;
	}
	return shader;
}

void Shader::attachShaderToProgram(uint32_t program) {
	glAttachShader(program, m_shader);
}

Shader::~Shader() {
	if (m_shader) {
		glDeleteShader(m_shader);
	}
}

bool Shader::load(const std::string& filePath, GLenum type) {
	std::optional<std::string> loadShaderFileResult = glload::loadShaderFile(filePath);
	if (!loadShaderFileResult.has_value()) {
		return false;
	}

	std::string code = loadShaderFileResult.value();
	int32_t codeLen = code.length();
	const char* codePtr = code.c_str();

	m_shader = glCreateShader(type);
	glShaderSource(m_shader, 1, &codePtr, &codeLen);
	glCompileShader(m_shader);


	int success = 0;

	glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
	
	if (!success) {
		char infoLog[1024];
		glGetShaderInfoLog(m_shader, 1024, nullptr, infoLog);
		std::cerr << "failed to compile shader" << std::endl;
		std::cerr << "reason: " << infoLog << std::endl;
		return false;
	}

	return true;
}