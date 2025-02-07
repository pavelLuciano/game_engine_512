#include "MyShader.h"

#define SHADER_COMP 0
#define PROGRAM_LINK 1

MyShader::MyShader(const char* vertex_shader, const char* fragment_shader)
{
    compileShaderProgram(vertex_shader,fragment_shader);
}
MyShader::~MyShader()
{
    glDeleteProgram(program_id);
}
void MyShader::use() const
{
    glUseProgram(program_id);
}
bool MyShader::compileShaderProgram(const char* vertex_shader_path, const char* fragment_shader_path)
{
    if (program_id != NO_COMPILED_PROGRAM) return false;

    std::stringstream vertex_stream;
    std::stringstream fragment_stream;
    std::ifstream vertex_file(vertex_shader_path);
    std::ifstream fragment_file(fragment_shader_path);
    std::string line, source_aux;

    std::cout << vertex_shader_path << std::endl;
    std::cout << fragment_shader_path << std::endl;

    if (!vertex_file.is_open() || !fragment_file.is_open())
        std::cout << "ERROR::SHADER::NO_SE_PUDIERON_ABRIR_LOS_SHADER" << std::endl;

    while (getline(vertex_file, line))
        vertex_stream << line << "\n";
    while  (getline(fragment_file, line))
        fragment_stream << line << "\n";
    
    std::string vertex_source = vertex_stream.str();
    std::string fragment_source = fragment_stream.str();

    std::cout << vertex_source << std::endl;
    std::cout << fragment_source << std::endl;

    //ACA SE COMPILAN LOS SHADERS
    unsigned int vertex, fragment;

    vertex = compileShader(GL_VERTEX_SHADER, vertex_source);
    checkCompileErrors(vertex, SHADER_COMP);

    fragment = compileShader(GL_FRAGMENT_SHADER, fragment_source);
    checkCompileErrors(fragment, SHADER_COMP);

    //ACA SE COMPILA EL PROGRAMA
    program_id = glCreateProgram();
    glAttachShader(program_id, vertex);
    glAttachShader(program_id, fragment);
    glLinkProgram(program_id);
    //Deberia poner aca una funcion para verificar si el programa se compilo correctamente
    checkCompileErrors(program_id, PROGRAM_LINK);
    
    glDeleteShader(vertex);
    glDeleteShader(fragment);
    return true;
}
unsigned int MyShader::compileShader(unsigned int type,std::string& source)
{
    unsigned int shader = glCreateShader(type);
    const char* shader_src = source.c_str();
    glShaderSource(shader, 1, &shader_src, NULL);
	glCompileShader(shader);
    return shader;
}
void MyShader::checkCompileErrors(unsigned int id, int type) const
{
    int success;
	char infoLog[512];
    if (type == SHADER_COMP) 
    {
        glGetShaderiv( id, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(id, 512, NULL, infoLog);
		    std::cout << "ERROR::SHADER::COMPILATION\n" << infoLog << std::endl;  
        }
        else std::cout << "SHADER::COMPILATION::SUCCESS"<<"\n";
    }
	if (type== PROGRAM_LINK)
    {
        glGetProgramiv(id, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(id, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::LINKING\n" << infoLog << std::endl;
        }
	    else std::cout << "SHADER::LINKING::SUCCESS"<<"\n";
    }

}
bool MyShader::isCompiled()
{
    return this->program_id != NO_COMPILED_PROGRAM;
}
void MyShader::setCamera(MyCamera camera)
{
    setMat4("view", camera.getViewMat());
    setMat4("projection", camera.getProjectionMat());
}
void MyShader::setMat4(const std::string& name, const glm::mat4& matrix) const
{
    glUniformMatrix4fv(glGetUniformLocation(program_id, name.c_str()), 1, GL_FALSE, &matrix[0][0]);
}