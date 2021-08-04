#ifndef __RENDERERCOMPOSER_H__
#define __RENDERERCOMPOSER_H__

#include "BackgroudnRenderer.h"
#include "FTriangleRenderer.h"
#include "Renderer.h"
#include "STriangleRenderer.h"
#include "vector"
#include "TextureRenderer.h"
using std::vector;

class RendererComposer : public Renderer {
   public:
    RendererComposer() {
        addRenderer(new BackgroundRenderer());
        // addRenderer(new FTriangleRenderer());
        // addRenderer(new STriangleRenderer());
        addRenderer(new TextureRenderer());
    }

    void addRenderer(Renderer* renderer) {
        renderers.push_back(renderer);
    }

    void doRender() {
        for (auto renderer : renderers) {
            renderer->doRender();
        }
    }
    ~RendererComposer() {
        for (auto renderer : renderers) {
            delete renderer;
        }
    }

   private:
    vector<Renderer*> renderers;
};

#endif  // __RENDERERCOMPOSER_H__