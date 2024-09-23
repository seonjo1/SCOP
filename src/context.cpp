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

	m_vertexArray = VertexArray::create();
	m_vertexBuffer = Buffer::create(GL_ARRAY_BUFFER, sizeof(float) * 20,
									vertices, GL_STATIC_DRAW);

	m_vertexArray->setAttribute(0, 3, sizeof(float) * 5, 0);
	m_vertexArray->setAttribute(1, 2, sizeof(float) * 5, sizeof(float) * 3);

	m_elementBuffer = Buffer::create(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * 6,
									indices, GL_STATIC_DRAW);

	m_program = Program::create("./shader/simple.vs", "./shader/simple.fs");

	if (!m_program) {
		return false;
	}

	m_image = Image::create("./image/sample.bmp");
	m_texture = Texture::create(m_image);


	return true;
}

void Context::Render() {

	glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glmath::mat4 model = glmath::scale(glmath::mat4(1.0f), glmath::vec3(2.0f));
	glmath::mat4 view = glmath::lookAt(glmath::vec3(0.0f, 0.0f, -3.0f), glmath::vec3(0.0f, 0.0f, 0.0f), glmath::vec3(0.0f, 1.0f, 0.0f));
	glmath::mat4 projection = glmath::perspective(glmath::radians(45.0f), (float)m_width / (float)m_height , 0.01f, 10.0f);
	glmath::mat4 transform = projection * view * model;

	m_program->useProgram();
	m_program->setUniform("tex", 0);
	m_program->setUniform("transform", transform);
	m_vertexArray->bind();
	m_texture->activeTexture(GL_TEXTURE0);
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}
