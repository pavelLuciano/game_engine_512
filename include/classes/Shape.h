#ifndef _SHAPE_H
#define _SHAPE_H
#include "Entity.h"
#include "iDrawable.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec3 color;
    glm::vec2 tex_coords;
};

class Shape: public Entity, IDrawable
{
public:
    unsigned int VAO;

    Shape(const char*);
    ~Shape();
    void draw(MyShader&) override;

    void printVertex()
    {
        for (auto v: vertex_data) printVertex(v);
    }

private:
    std::vector<Vertex> vertex_data;
    std::vector<unsigned int> indices;

    unsigned int VBO;
    unsigned int EBO;

    void setup();
    void loadFromFile(const char*);

    void printVertex(Vertex v)
    {
        std::cout << v.position[0] << " " << v.position[1] << " " << v.position[2] 
                  << " " << v.color[0] << " " << v.color[1] << " " << v.color[2] << std::endl;
    }


};

#endif