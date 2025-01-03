#include "MyShader.h"
#include <GL/glew.h>

MyShader::MyShader(const char* vertex_shader, const char* fragment_shader)
{
    setFragmentShader(fragment_shader);
    setVertexShader(vertex_shader);
    compileShaderProgram();
}
void MyShader::use() const
{
    glUseProgram(program_id);
}
bool MyShader::compileShaderProgram()
{
    if (program_id != NO_COMPILED_PROGRAM) return false;

    std::stringstream vertex_stream;
    std::stringstream fragment_stream;
    std::ifstream vertex_file;
    std::ifstream fragment_file;
    std::string line;

    vertex_file.open(vertex_shader_path);
    fragment_file.open(fragment_shader_path);
    if (!vertex_file.is_open() || !fragment_file.is_open())
        std::cout << "ERROR::SHADER::NO_SE_PUDIERON_ABRIR_LOS_SHADER" << std::endl;

    while (getline(vertex_file, line))
        vertex_stream << line << "\n";
    while  (getline(fragment_file, line))
        fragment_stream << line << "\n";
    
    const char* vertex_src = vertex_stream.str().c_str();
    const char* fragment_src = fragment_stream.str().c_str();

    //ACA SE COMPILAN LOS SHADERS
    unsigned int vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertex_src, NULL);
    glCompileShader(vertex);
    //Deberia poner aca una funcion para verificar si el shader se compilo correctamente

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragment_src, NULL);
    glCompileShader(fragment);
    //Deberia poner aca una funcion para verificar si el shader se compilo correctamente

    //ACA SE COMPILA EL PROGRAMA
    this->program_id = glCreateProgram();
    glAttachShader(this->program_id, vertex);
    glAttachShader(this->program_id, fragment);
    glLinkProgram(this->program_id);
    //Deberia poner aca una funcion para verificar si el programa se compilo correctamente

    glDeleteShader(vertex);
    glDeleteShader(fragment);
    return true;
}
bool MyShader::setVertexShader(const char* vertex_shader_path)
{
    if (isCompiled()) return false;
    this->vertex_shader_path = vertex_shader_path;
    return true;
}
bool MyShader::setFragmentShader(const char*  fragment_shader_path)
{
    if (isCompiled()) return false;
    this->vertex_shader_path = fragment_shader_path;
    return true;
}
bool MyShader::isCompiled()
{
    return this->program_id != NO_COMPILED_PROGRAM;
}