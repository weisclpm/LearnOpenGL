#include "RendererImpl.h"
#include "Window.h"

int main() {
    Window* window = Window::createWindow(800, 600, "Hahah");
    window->setRenderer(new RendererImpl());
    window->loop();
}