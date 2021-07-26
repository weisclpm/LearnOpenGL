#include "Shader.h"

Shader::Shader(ShaderType type, std::string shaderSource) : type(type) {
    shader = glCreateShader(convertType());
    if (shader) {
        const char* source = shaderSource.c_str();
        glShaderSource(shader, 1, &source, NULL);
        glCompileShader(shader);
    }
}

bool Shader::ready(std::string& errorInfo) {
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    char info[512];
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, info);
        errorInfo = info;
    }
    return success;
}

GLenum Shader::convertType() {
    switch (type) {
        case VERTEX: {
            return GL_VERTEX_SHADER;
        }
        case FRAGMENT: {
            return GL_FRAGMENT_SHADER;
        }
    }
    return 0;
}