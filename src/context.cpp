#include "../include/context.h"

void Context::Reshape(int width, int height) {
	m_width = width;
	m_height = height;
	glViewport(0, 0, m_width, m_height);
}
	
void Context::ProcessInput(GLFWwindow *window)
{	
	const static float objectSpeed = 0.025f;
	const static float rotateSpeed = 0.5f;
	static float transSpeed = -0.01;
	static bool keyTPressed = false;

	float degree = 0.0f;
	glmath::vec3 move(0.0f);
	
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		move = move + objectSpeed * m_cameraFront;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		move = move - objectSpeed * m_cameraFront;

	glmath::vec3 cameraRight = glmath::normalize(glmath::cross(m_cameraFront, m_cameraUp));
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		move = move + objectSpeed * cameraRight;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		move = move - objectSpeed * cameraRight;
	
	glmath::vec3 cameraUp = glmath::normalize(glmath::cross(cameraRight, m_cameraFront));
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		move = move + objectSpeed * cameraUp;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		move = move - objectSpeed * cameraUp;

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		degree = rotateSpeed;
	
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) {
        if (!keyTPressed) {
            transSpeed = -transSpeed;
            keyTPressed = true;
        }
    } else {
        keyTPressed = false;
    }
	
	m_model->updateModel(move, degree, transSpeed);
}

std::unique_ptr<Context> Context::create() {
	std::unique_ptr<Context> context(new Context());
	if (!context->init()) return nullptr;
	return context;
}

bool Context::init() {
	m_model = Model::create("./object/skull.obj");
	m_program = Program::create("./shader/simple.vs", "./shader/simple.fs");

	if (!m_program || !m_model) {
		return false;
	}

	m_image = Image::create("./image/texture.bmp");
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
	
	m_model->draw(m_program.get(), m_cameraPos, m_cameraUp, m_cameraFront);
}
