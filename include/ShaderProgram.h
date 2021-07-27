#ifndef __SHADERPROGRAM_H__
#define __SHADERPROGRAM_H__

#include <string>
#include <vector>

#include "Shader.h"

using std::string;
using std::vector;

class ShaderProgram {
   public:
    ShaderProgram();
    void attachShader(Shader& shader);
    void linkShader();
    bool ready(std::string& errInfo);

    GLuint mShaderProgram;
    string mShaderErrorInfo;
    vector<Shader*> mShaders;
};

#endif  // __SHADERPROGRAM_H__