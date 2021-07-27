#ifndef __SHADER_H__
#define __SHADER_H__
#include <string>

#include "GLEnv.h"

using std::string;

enum ShaderType {
    VERTEX,    // 顶点着色器
    FRAGMENT,  // 片段着色器
};

class Shader {
   public:
    Shader(ShaderType type, string shaderName, string shaderSource);

    void deleteShader();

    bool ready();

    GLuint mShader;

    string mShaderName;

   private:
    ShaderType mType;

    GLenum convertType();
};

#endif  // __SHADER_H__