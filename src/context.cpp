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
	
	m_model = Model::create("./object/42.obj");
	m_program = Program::create("./shader/simple.vs", "./shader/simple.fs");

	if (!m_program) {
		return false;
	}

	m_image = Image::create("./image/sample.bmp");
	m_texture = Texture::create(m_image);

	glEnable(GL_DEPTH_TEST);

	return true;
}

void Context::Render() {

	glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glmath::mat4 projection = glmath::perspective(glmath::radians(45.0f), (float)m_width / (float)m_height , 0.01f, 30.0f);

	m_program->useProgram();
	m_program->setUniform("tex", 0);
	m_program->setUniform("projection", projection);
	m_texture->activeTexture(GL_TEXTURE0);
	
	m_model->draw(m_program.get(), m_cameraPos, m_cameraUp);
}
