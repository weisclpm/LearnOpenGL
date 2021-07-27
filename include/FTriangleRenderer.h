#ifndef __FTRIANGLERENDERER_H__
#define __FTRIANGLERENDERER_H__

#include "Renderer.h"
#include "ShaderProgram.h"

class FTriangleRenderer : public Renderer {
   public:
    FTriangleRenderer() {
        Shader shaderVertex(VERTEX, vertexShaderSource);
        Shader shaderFragment(FRAGMENT, fragmentShaderSource);
        program.attachShader(shaderVertex);
        program.attachShader(shaderFragment);
        program.linkShader();

        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);

        float triangle[] = {
            0.0f, -0.5f, 0.0f,  // left
            0.9f, -0.5f, 0.0f,  // right
            0.45f, 0.5f, 0.0f   // top
        };

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), &triangle, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    void doRender() {
        glUseProgram(program.mShaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

   private:
    ShaderProgram program;
    GLuint VAO, VBO;

    static constexpr auto vertexShaderSource = R"delimiter(
                        #version 330 core
                        layout (location = 0) in vec3 aPos;
                        void main() {
                            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
                        }
                        )delimiter";

    static constexpr auto fragmentShaderSource = R"(
                        #version 330 core
                        out vec4 FragColor;
                        void main() {
                            FragColor = vec4(1.0f, 0.5f, 0.7f, 1.0f);
                        }
                        )";
};

#endif  // __FTRIANGLERENDERER_H__