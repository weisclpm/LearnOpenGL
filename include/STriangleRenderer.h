#ifndef __STRIANGLERENDERER_H__
#define __STRIANGLERENDERER_H__

#include "Renderer.h"
#include "Shader.h"

class STriangleRenderer : public Renderer {
   public:
    STriangleRenderer() : mShader(Shader(sVertexShaderSource, sFragmentShaderSource)) {
        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);

        float triangle[] = {
            -0.9f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,  // left
            -0.0f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,  // right
            -0.45f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f   // top
        };

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    void doRender() {
        mShader.use();
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

   private:
    Shader mShader;
    GLuint VAO, VBO;

    static constexpr auto sVertexShaderSource = R"(
                        #version 330 core
                        layout (location = 0) in vec3 aPos;
                        layout (location = 1) in vec3 aColor;
                        out vec3 outColor;
                        void main() {
                            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
                            outColor = aColor;
                        }
                        )";

    static constexpr auto sFragmentShaderSource = R"(
                        #version 330 core
                        out vec4 FragColor;
                        in vec3 outColor;
                        void main() {
                            FragColor = vec4(outColor, 1.0f);
                        }
                        )";
};
#endif  // __STRIANGLERENDERER_H__