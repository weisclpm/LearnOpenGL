#ifndef __TEXTURERENDERER_H__
#define __TEXTURERENDERER_H__
// 通过定义STB_IMAGE_IMPLEMENTATION，预处理器会修改头文件，
// 让其只包含相关的函数定义源码，等于是将这个头文件变为一个 .cpp 文件了
#define STB_IMAGE_IMPLEMENTATION
#include "Renderer.h"
#include "Shader.h"
#include "stb_image.h"

class TextureRenderer : public Renderer {
   public:
    TextureRenderer() : shader(Shader("../shader/TextureVertexShader.vs", "../shader/TextureFragmentShader.fs")) {
        // 初始化纹理
        initTex();
        // 初始化顶点数据
        initAttrib();
    }

    void doRender() {
        glBindTexture(GL_TEXTURE_2D, textureId);
        shader.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    }

   private:
    GLuint textureId;
    GLuint VAO, VBO, EBO;
    Shader shader;

    void initTex() {
        // 创建纹理
        glGenTextures(1, &textureId);
        // 绑定纹理
        glBindTexture(GL_TEXTURE_2D, textureId);

        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        int width, height, nrChannels;  // 宽、高、颜色通道
        unsigned char* data = stbi_load(R"(../image/container.jpeg)", &width, &height, &nrChannels, 0);

        if (data) {
            // 生成纹理数据
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            // 生成多级渐远纹理
            glGenerateMipmap(GL_TEXTURE_2D);
        } else {
            std::cout << "Failed to load texture" << std::endl;
        }

        stbi_image_free(data);
    }

    void initAttrib() {
        float vertices[] = {
            //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
            0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f,    // 右上
            0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,  // 左下
            -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f    // 左上
        };
        unsigned int indices[] = {
            0, 1, 3,  // first triangle
            1, 2, 3   // second triangle
        };

        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);
        glGenVertexArrays(1, &VAO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
    }
};

#endif  // __TEXTURERENDERER_H__