#ifndef SHADER_H
#define SHADER_H

#include "MyCamera.h"

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>

#define NO_COMPILED_PROGRAM -1

class MyShader
{
public:
    unsigned int program_id = NO_COMPILED_PROGRAM;

    //constructores
    MyShader(const char*, const char*);
    MyShader(const char*);
    //MyShader();
    //destructor
    ~MyShader();
    //metodos
    //getters
    unsigned int getID() const;
    void use() const;
    bool isCompiled();

    
    void setCamera(MyCamera);
    void setMat4(const std::string& name, const glm::mat4& matrix) const;

private:
    bool compileShaderProgram(const char*, const char*);
    unsigned int compileShader(unsigned int, std::string&);
    void checkCompileErrors(unsigned int, int) const;
    
};

#endif