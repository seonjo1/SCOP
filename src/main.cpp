#include "../include/scop.h"
#include "../include/context.h"

void OnFramebufferSizeChange(GLFWwindow* window, int width, int height) {
	Context* context = (Context *)glfwGetWindowUserPointer(window);
	context->Reshape(width, height);
}

void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main(int argc, const char** argv) {

	std::cout << "Start program" << std::endl;

	std::cout << "Initialize glfw" << std::endl;
	if (!glfwInit()) {
		const char* description = nullptr;
		glfwGetError(&description);
		std::cerr << "failed to initialize glfw: " << description << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);;
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	
	std::cout << "Create glfw window" << std::endl;
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);
	if (!window) {
		std::cerr << "failed to create glfw window" << std::endl;
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cerr << "failed to initialize glad" << std::endl;
		glfwTerminate();
		return -1;
	}

	std::unique_ptr<Context> context = Context::create();
	if (!context) {
		std::cout << "failed to create context" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowUserPointer(window, context.get());

	OnFramebufferSizeChange(window, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChange);
	glfwSetKeyCallback(window, OnKeyEvent);

	std::cout << "Start main loop" << std::endl;
	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		context->ProcessInput(window);
		context->Render();
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}