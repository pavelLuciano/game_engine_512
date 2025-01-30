#ifndef _ENTITY_H
#define _ENTITY_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Entity
{
public:
    Entity();


    float x(){return transform._x;}
    float y(){return transform._y;}
    float z(){return transform._z;}
    float pitch(){return transform._pitch;}
    float yaw(){return transform._yaw;}
    float roll(){return transform._roll;}
    glm::vec3 getPosition();
    glm::vec3 getRotation();
    glm::vec3 getScale();

    void setX(float);
    void setY(float);
    void setZ(float);

    void setPitch(float);
    void setYaw(float);
    void setRoll(float);

    void rotateX(float);
    void rotateY(float);
    void rotateZ(float);

    void scaleX(float);
    void scaleY(float);
    void scaleZ(float);


private:
    struct Transform
    {
        //position
        float _x;
        float _y;
        float _z;
        //rotate
        float _pitch;
        float _yaw;
        float _roll;
        //scale
        float _scaleX;
        float _scaleY;
        float _scaleZ;
    } transform;




};

#endif