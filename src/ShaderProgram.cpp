#include "ShaderProgram.h"

#include <iostream>

ShaderProgram::ShaderProgram() {
    shaderProgram = glCreateProgram();
}

void ShaderProgram::attachShader(Shader& shader) {
    if (shaderProgram && shader.ready(shaderErrorInfo)) {
        glAttachShader(shaderProgram, shader.shader);
    }
}

void ShaderProgram::linkShader() {
    if (shaderProgram) {
        glLinkProgram(shaderProgram);
    }
}

bool ShaderProgram::ready(std::string& errInfo) {
    if(!shaderErrorInfo.empty()){
        errInfo = shaderErrorInfo;
        return false;
    }

    GLint success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        errInfo = infoLog;
    }
    return success;
}
