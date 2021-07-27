#include "Shader.h"

Shader::Shader(ShaderType type, string shaderName, string shaderSource) : mType(type), mShaderName(shaderName) {
    mShader = glCreateShader(convertType());
    if (mShader) {
        const char* source = shaderSource.c_str();
        glShaderSource(mShader, 1, &source, NULL);
        glCompileShader(mShader);
    }
}

bool Shader::ready() {
    GLint success;
    glGetShaderiv(mShader, GL_COMPILE_STATUS, &success);
    char info[512];
    if (!success) {
        glGetShaderInfoLog(mShader, 512, NULL, info);
        cout << "ERROR::FAILED TO COMPILE SHADER - " << mShaderName << ": " << endl;
    }
    return success;
}

GLenum Shader::convertType() {
    switch (mType) {
        case VERTEX: {
            return GL_VERTEX_SHADER;
        }
        case FRAGMENT: {
            return GL_FRAGMENT_SHADER;
        }
    }
    return 0;
}
void Shader::deleteShader() {
    if (mShader) {
        glDeleteShader(mShader);
    }
}
