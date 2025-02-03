#include "Shape.h"
#include <fstream>
#include <sstream>
#include <vector>

//falta una funcion que analice el formato y modularizar mas aun esto
Shape::Shape(const char* file_path): Entity()
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
        VERTICES = 0, COLORS, INDICES
    };
    std::ifstream vertex_data_file(file_path);
    std::string line;
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;

    Mode current_mode = INDICES;
    while(getline(vertex_data_file, line))
    {
        if (line.find("VERTICES") != std::string::npos) 
        {
            current_mode = VERTICES;
            getline(vertex_data_file, line);
        }
        if (line.find("COLORS")  != std::string::npos)
        {
            current_mode = COLORS;
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
                vertices.push_back(glm::vec3(std::stof(x), std::stof(y), std::stof(z)));
            }
            break;
            case COLORS:
            {
                std::istringstream iss(line);
                std::string R, G, B;
                iss >> R;
                iss >> G;
                iss >> B;
                colors.push_back (glm::vec3(std::stof(R), std::stof(G), std::stof(B)));
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
    for (int i = 0; i< vertices.size(); i++)
    {
        this->vertex_data.push_back({vertices[i], colors[i], glm::vec2(0.0f,0.0f)});
    }
    vertex_data_file.close();
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
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, getPosition());
    model = glm::scale(model, getScale());
    model = glm::rotate(model, glm::radians(pitch()), glm::vec3(1,0,0));
    model = glm::rotate(model, glm::radians(yaw()), glm::vec3(0,1,0));
    model = glm::rotate(model, glm::radians(roll()), glm::vec3(0,0,1));
    shader.setMat4("model", model);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}