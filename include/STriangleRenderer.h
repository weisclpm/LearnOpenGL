#ifndef __STRIANGLERENDERER_H__
#define __STRIANGLERENDERER_H__

#include "Renderer.h"
#include "ShaderProgram.h"

class STriangleRenderer : public Renderer {
   public:
    STriangleRenderer() {
        Shader shaderVertex(VERTEX, vertexShaderSource);
        Shader shaderFragment(FRAGMENT, fragmentShaderSource);
        program.attachShader(shaderVertex);
        program.attachShader(shaderFragment);
        program.linkShader();

        glGenBuffers(1, &VBO);
        glGenVertexArrays(1, &VAO);

        float triangle[] = {
            -0.9f, -0.5f, 0.0f,  // left
            -0.0f, -0.5f, 0.0f,  // right
            -0.45f, 0.5f, 0.0f,  // top
        };

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(triangle), triangle, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    void doRender() {
        glUseProgram(program.shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }

   private:
    ShaderProgram program;
    GLuint VAO, VBO;

    const char* vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";

    const char* fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.3f, 0.4f, 1.0f);\n"
        "}\0";
};
#endif  // __STRIANGLERENDERER_H__