#include "../include/scop.h"

void OnFramebufferSizeChange(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void OnKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void Render() {
    glClearColor(0.1f, 0.2f, 0.3f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

int main(int argc, const char** argv) {
    // 시작을 알리는 로그
    SPDLOG_INFO("Start program");

	// glfw 라이브러리 초기화, 실패하면 에러 출력후 종료
    SPDLOG_INFO("Initialize glfw");
    if (!glfwInit()) {
        const char* description = nullptr;
        glfwGetError(&description);
        SPDLOG_ERROR("failed to initialize glfw: {}", description);
        return -1;
	}

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);;
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	 // glfw 윈도우 생성, 실패하면 에러 출력후 종료
    SPDLOG_INFO("Create glfw window");
    auto window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_NAME, nullptr, nullptr);
    if (!window) {
        SPDLOG_ERROR("failed to create glfw window");
        glfwTerminate();
        return -1;
	}
    
    glfwMakeContextCurrent(window);

    // glad를 활용한 OpenGL 함수 로딩
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        SPDLOG_ERROR("failed to initialize glad");
        glfwTerminate();
        return -1;
    }
	
    // ... context 지정 부분

    OnFramebufferSizeChange(window, WINDOW_WIDTH, WINDOW_HEIGHT);
    glfwSetFramebufferSizeCallback(window, OnFramebufferSizeChange);
    glfwSetKeyCallback(window, OnKeyEvent);


    SPDLOG_INFO("Start main loop");
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        Render();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}