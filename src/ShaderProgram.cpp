#include "ShaderProgram.h"

#include <iostream>

ShaderProgram::ShaderProgram() {
    mShaderProgram = glCreateProgram();
}

void ShaderProgram::attachShader(Shader& shader) {
    if (mShaderProgram && shader.ready(mShaderErrorInfo)) {
        glAttachShader(mShaderProgram, shader.mShader);
        mShaders.push_back(&shader);
    }
}

void ShaderProgram::linkShader() {
    if (mShaderProgram) {
        glLinkProgram(mShaderProgram);
        for (auto shader : mShaders) {
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
