#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() {
    mShaderProgram = glCreateProgram();
}

void ShaderProgram::attachAndLinkShader(initializer_list<Shader*> shaders) {
    if (mShaderProgram) {
        for (auto shader : shaders) {
            if (shader->ready()) {
                glAttachShader(mShaderProgram, shader->mShader);
            } else {
                return;
            }
        }
        glLinkProgram(mShaderProgram);

        // 链接成功以后，可以删除创建的着色器
        for (auto shader : shaders) {
            shader->deleteShader();
        }
    }
}

bool ShaderProgram::ready() {
    GLint success;
    char infoLog[512];
    glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(mShaderProgram, 512, NULL, infoLog);
        cout << "ERROR::FAILED TO LINK SHADER PROGRAM: " << infoLog << endl;
    }
    return success;
}
