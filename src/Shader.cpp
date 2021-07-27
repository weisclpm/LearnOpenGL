#include "Shader.h"

void compileShader(GLuint shader, string source, string tag);

Shader::Shader(string vertexSource, string fragmentSource) {
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    compileShader(vertexShader, vertexSource, "vertex");
    compileShader(fragmentShader, fragmentSource, "fragment");

    mProgram = glCreateProgram();
    glAttachShader(mProgram, vertexShader);
    glAttachShader(mProgram, fragmentShader);
    glLinkProgram(mProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLint success;
    char infoLog[512];
    glGetProgramiv(mProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(mProgram, 512, NULL, infoLog);
        cout << "ERROR::FAILED TO LINK SHADER PROGRAM: " << infoLog << endl;
    }
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

    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    char info[512];
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, info);
        cout << "ERROR::FAILED TO COMPILE SHADER - " << tag << " : " << info << endl;
    }
}
