#ifndef _BOX_H
#define _BOX_H

#include "Entity.h"
#include "iDrawable.h"

class Box: public Entity, IDrawable
{

public:
    unsigned int VAO;
    unsigned int EBO;
    // Datos de los vértices del cubo con colores RGB asociados
    float vertices[48] = {
        // Posición (x, y, z)       // Color (r, g, b)
         0.5f,  0.5f,  0.5f,       1.0f, 0.0f, 0.0f, // Vértice 0: Frente arriba derecha (rojo)
         0.5f, -0.5f,  0.5f,       0.0f, 1.0f, 0.0f, // Vértice 1: Frente abajo derecha (verde)
        -0.5f, -0.5f,  0.5f,       0.0f, 0.0f, 1.0f, // Vértice 2: Frente abajo izquierda (azul)
        -0.5f,  0.5f,  0.5f,       1.0f, 1.0f, 0.0f, // Vértice 3: Frente arriba izquierda (amarillo)
         0.5f,  0.5f, -0.5f,       1.0f, 0.0f, 1.0f, // Vértice 4: Atrás arriba derecha (magenta)
         0.5f, -0.5f, -0.5f,       0.0f, 1.0f, 1.0f, // Vértice 5: Atrás abajo derecha (cian)
        -0.5f, -0.5f, -0.5f,       0.5f, 0.5f, 0.5f, // Vértice 6: Atrás abajo izquierda (gris)
        -0.5f,  0.5f, -0.5f,       1.0f, 1.0f, 1.0f  // Vértice 7: Atrás arriba izquierda (blanco)
    };
    // Índices que definen los triángulos del cubo
    unsigned int indices[36] = {
        // Cara frontal
        0, 1, 3,   1, 2, 3,
        // Cara superior
        4, 0, 7,   0, 3, 7,
        // Cara trasera
        5, 4, 6,   4, 7, 6,
        // Cara inferior
        1, 5, 2,   5, 6, 2,
        // Cara derecha
        4, 5, 0,   5, 1, 0,
        // Cara izquierda
        3, 2, 7,   2, 6, 7
    };
    unsigned int VBO;
    // Constructor
    Box()
    {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, 48 * sizeof(float), &vertices[0], GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));


        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36*sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        glBindVertexArray(0);
    }

    void draw(MyShader &shader)
    {
        shader.use();
        
        glm::mat4 model = glm::mat4(1.0f);
        
        model = glm::translate(model, getPosition());
        model = glm::rotate(model, glm::radians(pitch()), glm::vec3(1,0,0));
        model = glm::rotate(model, glm::radians(yaw()), glm::vec3(0,1,0));
        model = glm::rotate(model, glm::radians(roll()), glm::vec3(0,0,1));
        
        shader.setMat4("model", model);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

};

#endif