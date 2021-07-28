#ifndef __SHADER_H__
#define __SHADER_H__
#include <string>

#include "GLEnv.h"

using std::string;

class Shader {
   public:
    Shader(string vertexSourcePath, string fragmentSourcePath);

    void use();

    int getUniformLocation(string name);

   private:
    GLuint mProgram;
};

#endif  // __SHADER_H__