#include "ShaderProgram.h"

ShaderProgram::ShaderProgram() {
    mShaderProgram = glCreateProgram();
}

void ShaderProgram::attachAndLinkShader(initializer_list<Shader*> shaders) {
    if (mShaderProgram) {
        for (auto shader : shaders) {
            glAttachShader(mShaderProgram, shader->mShader);
        }
        glLinkProgram(mShaderProgram);

        // 链接成功以后，可以删除创建的着色器
        for (auto shader : shaders) {
            shader->deleteShader();
        }
    }
}

bool ShaderProgram::ready(std::string& errInfo) {
    if (!mShaderErrorInfo.empty()) {
        errInfo = mShaderErrorInfo;
        return false;
    }

    GLint success;
    char infoLog[512];
    glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(mShaderProgram, 512, NULL, infoLog);
        errInfo = infoLog;
    }
    return success;
}
