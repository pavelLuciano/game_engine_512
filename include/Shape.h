#ifndef _SHAPE_H
#define _SHAPE_H
#include <glm/glm.hpp>
#include "Entity.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 tex_coords;
};

class Shape: public Entity
{
public:
    unsigned int VAO;

    Shape(const char*);
    ~Shape();
    void draw(MyShader&) override;

private:
    std::vector<Vertex> vertex_data;
    std::vector<unsigned int> indices;

    unsigned int VBO;
    unsigned int EBO;

    void setup();
    void loadFromFile(const char*);
};

#endif