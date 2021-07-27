#include "Shader.h"

void compileShader(GLuint shader, string source, string tag);

void checkError(string type, GLuint object);

Shader::Shader(string vertexSource, string fragmentSource) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    compileShader(vertexShader, vertexSource, "VERTEX");
    compileShader(fragmentShader, fragmentSource, "FRAGMENT");

    mProgram = glCreateProgram();
    glAttachShader(mProgram, vertexShader);
    glAttachShader(mProgram, fragmentShader);
    glLinkProgram(mProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    checkError("PROGRAM", mProgram);
}

void Shader::use() {
    glUseProgram(mProgram);
}

int Shader::getUniformLocation(string name) {
    return glGetUniformLocation(mProgram, name.c_str());
}

void compileShader(GLuint shader, string source, string tag) {
    auto vSrc = source.c_str();
    glShaderSource(shader, 1, &vSrc, NULL);
    glCompileShader(shader);
    checkError(tag, shader);
}

void checkError(string type, GLuint object) {
    GLint success;
    char info[1024];
    if (type != "PROGRAM") {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(object, 1024, NULL, info);
            cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << " : " << info << endl;
        }
    } else {
        glGetProgramiv(object, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(object, 1024, NULL, info);
            cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << " : " << info << endl;
        }
    }
}
