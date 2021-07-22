#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

/**
 * 向glfw窗口注册的回调函数，窗口大小改变时，修改视口大小
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    cout << "window size change -> width: " << width << "height: " << height << endl;
}

/**
 * 处理窗口的输入事件
 */
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

/**
 * 渲染循环 
 */
void doRenderLoop(GLFWwindow* window) {
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        // 状态设置函数
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // 状态使用函数，它使用上面这行设置的颜色来清屏
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

int main() {
    // 初始化glfw Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // MacOS
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        cout << "failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // GLAD是用来管理OpenGL的函数指针的，所以在调用任何OpenGL的函数之前，我们需要初始化GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "failed to initialized glad" << endl;
        return -1;
    }

    // 开始渲染之前，必须告诉opengl窗口的尺寸大小
    // 前两个参数控制窗口左下角的位置，后两个参数就是宽和高
    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    doRenderLoop(window);

    glfwTerminate();

    return 0;
}