#ifndef __FTRIANGLERENDERER_H__
#define __FTRIANGLERENDERER_H__

#include <cmath>

#include "Renderer.h"
#include "Shader.h"

class FTriangleRenderer : public Renderer {
   public:
    FTriangleRenderer() : mShader(Shader(sVertexShaderSource, sFragmentShaderSource)) {
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
        float timeValue = glfwGetTime();
        float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = mShader.getUniformLocation("ourColor");
        mShader.use();
        // 更新uniform之前必须先使用glUseProgram
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

   private:
    Shader mShader;
    GLuint VAO, VBO;

    static constexpr auto sVertexShaderSource = R"(../shader/TriangleVertex.vs)";

    static constexpr auto sFragmentShaderSource = R"(../shader/FTriangleFragment.fs)";
};

#endif  // __FTRIANGLERENDERER_H__