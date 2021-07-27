#ifndef __BACKGROUDNRENDERER_H__
#define __BACKGROUDNRENDERER_H__
#include "Renderer.h"

class BackgroundRenderer : public Renderer {
   public:
    void doRender() {
        // 状态设置函数
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // 状态使用函数，它使用上面这行设置的颜色来清屏
        glClear(GL_COLOR_BUFFER_BIT);
    }
};

#endif  // __BACKGROUDNRENDERER_H__