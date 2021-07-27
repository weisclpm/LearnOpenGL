#include "RendererComposer.h"
#include "Window.h"

int main() {
    Window* window = Window::createWindow(800, 600, "Hahah");
    window->setRenderer(new RendererComposer());
    window->loop();
}