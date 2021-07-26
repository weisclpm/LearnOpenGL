#ifndef __WINDOW_H__
#define __WINDOW_H__
#include "GLEnv.h"
#include "Renderer.h"
#include <string>

class Window {
   public:
    static Window* createWindow(int width, int height, std::string title);
    void loop();
    void setRenderer(Renderer* renderer);

   private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    static Window* sWindowPtr;

    Window(int width, int height, std::string title);
    ~Window();

    int windowWidth;
    int windowHeight;
    std::string title;
    std::string errorMsg;
    GLFWwindow* window;
    Renderer* renderer;
};

#endif  // __WINDOW_H__