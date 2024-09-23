#include "../include/context.h"

void Context::Reshape(int width, int height) {
	m_width = width;
	m_height = height;
	glViewport(0, 0, m_width, m_height);
}

std::unique_ptr<Context> Context::create() {
	std::unique_ptr<Context> context(new Context());
	if (!context->init()) return nullptr;
	return context;
}

bool Context::init() {

	float vertices[] = { 
		0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
	};

	uint32_t indices[] = {
		0, 3, 1,
		1, 3, 2,
	};

	

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 20, vertices,  GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (const void*)(sizeof(float) * 3));

	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 6, indices,  GL_STATIC_DRAW);

	std::optional<std::string> loadVertexShaderFileResult = glload::loadShaderFile("./shader/simple.vs");
	std::optional<std::string> loadFragmentShaderFileResult = glload::loadShaderFile("./shader/simple.fs");
	
	if (!loadVertexShaderFileResult.has_value() || !loadFragmentShaderFileResult.has_value()) {
		return false;
	}

	std::string vsCode = loadVertexShaderFileResult.value();
	std::string fsCode = loadFragmentShaderFileResult.value();

	int32_t vsCodeLen = vsCode.length();
	int32_t fsCodeLen = fsCode.length();

	const char* vsCodePtr = vsCode.c_str();
	const char* fsCodePtr = fsCode.c_str();

	m_vertexShader = glCreateShader(GL_VERTEX_SHADER);	
	m_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(m_vertexShader, 1, &vsCodePtr, &vsCodeLen);
	glShaderSource(m_fragmentShader, 1, &fsCodePtr, &fsCodeLen);

	glCompileShader(m_vertexShader);

	int success = 0;

	glGetShaderiv(m_vertexShader, GL_COMPILE_STATUS, &success);
	
	if (!success) {
		char infoLog[1024];
		glGetShaderInfoLog(m_vertexShader, 1024, nullptr, infoLog);
		std::cout << "failed to compile vertex shader" << std::endl;
		std::cout << "reason: " << infoLog << std::endl;
		return false;
	}
	
	glCompileShader(m_fragmentShader);

	success = 0;

	glGetShaderiv(m_fragmentShader, GL_COMPILE_STATUS, &success);
		
	if (!success) {
		char infoLog[1024];
		glGetShaderInfoLog(m_fragmentShader, 1024, nullptr, infoLog);
		std::cout << "failed to compile fragment shader" << std::endl;
		std::cout << "reason: " << infoLog << std::endl;
		return false;
	}

	m_program = glCreateProgram();

	glAttachShader(m_program, m_vertexShader);
	glAttachShader(m_program, m_fragmentShader);
	glLinkProgram(m_program);

	
	success = 0;
	glGetProgramiv(m_program, GL_LINK_STATUS, &success);
	if (!success)
	{
		char infoLog[1024];
		glGetProgramInfoLog(m_program, 1024, nullptr, infoLog);
		std::cout << "failed to link program: " << infoLog << std::endl;
		return false;
	}

	m_image = glload::loadBmpImg("./image/sample.bmp", &m_texWidth, &m_texHeight, &m_texChannelCount);

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	GLenum format = GL_RGBA;
	switch (m_texChannelCount) {
		default: break;
		case 2: format = GL_RG; break;
		case 3: format = GL_BGR; break;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_texWidth, m_texHeight,
					0, format, GL_UNSIGNED_BYTE, m_image.get());

	glGenerateMipmap(GL_TEXTURE_2D);

	glUseProgram(m_program);

	
	GLuint location = glGetUniformLocation(m_program, "tex");
	glUniform1i(location, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	return true;
}

void Context::Render() {
	glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glmath::mat4 model(1.0f);
	glmath::mat4 view = glmath::lookAt(glmath::vec3(0.0f, 0.0f, -3.0f), glmath::vec3(0.0f, 0.0f, 0.0f), glmath::vec3(0.0f, 1.0f, 0.0f));
	glmath::mat4 projection = glmath::perspective(glmath::radians(45.0f), (float)m_width / (float)m_height , 0.01f, 10.0f);
	glmath::mat4 transform = projection * view * model;

	GLuint location = glGetUniformLocation(m_program, "transform");
	glUniformMatrix4fv(location, 1, GL_FALSE, glmath::value_ptr(transform));
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

Context::~Context() {

	if (m_vbo) {
		glDeleteBuffers(1, &m_vbo);
	}

	if (m_ebo) {
		glDeleteBuffers(1, &m_ebo);
	}

	if (m_vertexShader) {
		glDeleteShader(m_vertexShader);
	}

	if (m_fragmentShader) {
		glDeleteShader(m_fragmentShader);
	}
	
	if (m_program) {
		glDeleteProgram(m_program);
	}
	
	if (m_texture) {
		glDeleteTextures(1, &m_texture);
	}
}
