#ifndef __SHADERPROGRAM_H__
#define __SHADERPROGRAM_H__

#include <string>
#include <initializer_list>

#include "Shader.h"

using std::string;
using std::initializer_list;

class ShaderProgram {
   public:
    ShaderProgram();
    void attachAndLinkShader(initializer_list<Shader*> shaders);
    bool ready(std::string& errInfo);

    GLuint mShaderProgram;
    string mShaderErrorInfo;
};

#endif  // __SHADERPROGRAM_H__