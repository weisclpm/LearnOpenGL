#ifndef __RENDERER_H__
#define __RENDERER_H__

class Renderer {
    public:
    virtual void doRender() = 0;
    virtual ~Renderer() {};
};

#endif  // __RENDERER_H__