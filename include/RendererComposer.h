#ifndef __RENDERERCOMPOSER_H__
#define __RENDERERCOMPOSER_H__

#include "BackgroudnRenderer.h"
#include "FTriangleRenderer.h"
#include "Renderer.h"
#include "STriangleRenderer.h"
#include "vector"
using std::vector;

class RendererComposer : public Renderer {
   public:
    RendererComposer() {
        addRenderer(new BackgroundRenderer());
        addRenderer(new FTriangleRenderer());
        addRenderer(new STriangleRenderer());
    }

    void addRenderer(Renderer* renderer) {
        renderers.push_back(renderer);
    }

    void doRender() {
        for (auto renderer : renderers) {
            renderer->doRender();
        }
    }

   private:
    vector<Renderer*> renderers;
};

#endif  // __RENDERERCOMPOSER_H__