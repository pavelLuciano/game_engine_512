#ifndef SHADER_H
#define SHADER_H

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
    unsigned int program_id;
    const char* vertex_shader_path;
    const char* fragment_shader_path;
    //constructores
    MyShader(const char*, const char*);
    MyShader(const char*);
    MyShader();
    //destructor
    ~MyShader();
    //metodos
    //getters
    unsigned int getID() const;
    void use() const;
    //setters
    bool setVertexShader(const char*);
    bool setFragmentShader(const char*);

private:
    bool compileShaderProgram();
    void checkCompileErrors() const;
    bool isCompiled();
};

#endif