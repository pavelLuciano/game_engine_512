#ifndef _SHAPE_H
#define _SHAPE_H
#include <glm/glm.hpp>
#include "iDrawable.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 tex_coords;
};

class Shape: public IDrawable
{
public:
    unsigned int VAO;

    Shape(std::string);
    //~Shape(){};
    void draw(MyShader) override;

private:
    std::vector<Vertex> vertex_data;
    std::vector<unsigned int> indices;
    unsigned int VBO;
    unsigned int EBO;

    void setup();
    void loadFromFile(const char*);
};

#endif