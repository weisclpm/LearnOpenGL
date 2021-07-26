#ifndef __RENDERERIMPL_H__
#define __RENDERERIMPL_H__

#include "GLEnv.h"
#include "Renderer.h"
#include "ShaderProgram.h"

class RendererImpl : public Renderer {
   public:
    RendererImpl() {
        Shader shader1(VERTEX, vertexShaderSource);
        Shader shader2(FRAGMENT, fragmentShaderSource);
        Shader shader3(FRAGMENT, fragmentShaderSource2);
        program1.attachShader(shader1);
        program1.attachShader(shader2);
        program2.attachShader(shader1);
        program2.attachShader(shader3);

        program1.linkShader();
        program2.linkShader();

        float firstTriangle[] = {
            -0.9f, -0.5f, 0.0f,  // left
            -0.0f, -0.5f, 0.0f,  // right
            -0.45f, 0.5f, 0.0f,  // top
        };
        float secondTriangle[] = {
            0.0f, -0.5f, 0.0f,  // left
            0.9f, -0.5f, 0.0f,  // right
            0.45f, 0.5f, 0.0f   // top
        };

        glGenVertexArrays(2, VAO);
        glGenBuffers(2, VBO);

        // 1. 绑定VAO
        glBindVertexArray(VAO[0]);
        // 2. 复制顶点数组到缓冲里
        glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);
        // 3. 设置顶点属性指针
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(VAO[1]);
        glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    void doRender() {
        // 状态设置函数
        glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
        // 状态使用函数，它使用上面这行设置的颜色来清屏
        glClear(GL_COLOR_BUFFER_BIT);

        std::string errorInfo;
        if (program1.ready(errorInfo)) {
            glUseProgram(program1.shaderProgram);
            glBindVertexArray(VAO[0]);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        if (program2.ready(errorInfo)) {
            glUseProgram(program2.shaderProgram);
            glBindVertexArray(VAO[1]);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }
    }

   private:
    ShaderProgram program1, program2;

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

    const char* fragmentShaderSource2 =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.7f, 1.0f);\n"
        "}\0";

    GLuint VBO[2], VAO[2];
};

#endif  // __RENDERERIMPL_H__