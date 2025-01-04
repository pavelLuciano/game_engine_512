#include "Shape.h"
#include <fstream>
#include <sstream>
#include <vector>



//falta una funcion que analice el formato y modularizar mas aun esto
Shape::Shape(const char* file_path)
{
    loadFromFile(file_path);
    setup();
}
Shape::~Shape()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}
void Shape::loadFromFile(const char* file_path)
{
    enum Mode
    {
        VERTICES = 0, INDICES
    };
    std::ifstream vertex_data_file(file_path);
    std::string line;

    Mode current_mode = INDICES;
    while(getline(vertex_data_file, line))
    {
        if (line.find("VERTICES") != std::string::npos) 
        {
            current_mode = VERTICES;
            getline(vertex_data_file, line);
        }
        if (line.find("INDICES")  != std::string::npos)
        {
            current_mode = INDICES;
            getline(vertex_data_file, line);
        }
        switch (current_mode)
        {
            case VERTICES:
            {
                std::istringstream iss(line);
                std::string x, y, z;
                iss >> x;
                iss >> y;
                iss >> z;
                this->vertex_data.push_back({
                        glm::vec3(std::stof(x), std::stof(y), std::stof(y)),
                        glm::vec3(1.0f, 0.0f, 0.0f),
                        glm::vec2(0.0f, 0.0f)
                });
            }
            break;
            case INDICES:
            {
                std::istringstream iss(line);
                std::string ind;
                while(iss >> ind) this->indices.push_back(std::stoi(ind));
            }
            break;
        }
    }
}
void Shape::setup()
{
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertex_data.size()* sizeof(Vertex), &vertex_data[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coords));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,indices.size()*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}
//overrides
void Shape::draw(MyShader &shader)
{
    shader.use();
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}