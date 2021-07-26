#include "Window.h"

Window* Window::sWindowPtr;

// TODO 加锁
Window* Window::createWindow(int width, int height, std::string title) {
    if (sWindowPtr) {
        return sWindowPtr;
    }
    sWindowPtr = new Window(width, height, title);
    return sWindowPtr;
}

void Window::loop() {
    if (window == NULL) {
        return;
    }

    while (!glfwWindowShouldClose(window)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            glfwSetWindowShouldClose(window, true);
        }

        if (renderer) {
            renderer->doRender();
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Window::setRenderer(Renderer* renderer) {
    this->renderer = renderer;
}

Window::Window(int width, int height, std::string title) : windowWidth(width), windowHeight(height), title(title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    window = glfwCreateWindow(windowWidth, windowHeight, title.c_str(), NULL, NULL);
    if (window == NULL) {
        errorMsg = "failed to create GLFW window";
        return;
    }

    glfwMakeContextCurrent(window);

    // GLAD是用来管理OpenGL的函数指针的，所以在调用任何OpenGL的函数之前，我们需要初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        return;
    }

    // 开始渲染之前，必须告诉opengl窗口的尺寸大小
    // 前两个参数控制窗口左下角的位置，后两个参数就是宽和高
    glViewport(0, 0, windowWidth, windowHeight);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

Window::~Window() {
    glfwTerminate();
    delete renderer;
    delete sWindowPtr;
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
