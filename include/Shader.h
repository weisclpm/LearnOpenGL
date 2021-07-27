#ifndef __SHADER_H__
#define __SHADER_H__
#include <string>

#include "GLEnv.h"

enum ShaderType {
    VERTEX,    // 顶点着色器
    FRAGMENT,  // 片段着色器
};

class Shader {
   public:
    Shader(ShaderType type, std::string shaderSource);

    void deleteShader();

    bool ready(std::string& errorInfo);

    GLuint mShader;

   private:
    ShaderType mType;

    GLenum convertType();
};

#endif  // __SHADER_H__