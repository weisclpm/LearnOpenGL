#ifndef __SHADERPROGRAM_H__
#define __SHADERPROGRAM_H__

#include <string>

#include "Shader.h"

class ShaderProgram {
   public:
    ShaderProgram();
    void attachShader(Shader& shader);
    void linkShader();
    bool ready(std::string& errInfo);

    GLuint shaderProgram;
    std::string shaderErrorInfo;
};

#endif  // __SHADERPROGRAM_H__