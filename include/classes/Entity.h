#ifndef _ENTITY_H
#define _ENTITY_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Entity
{
public:
    Entity();


    float x(){return transform.x;}
    float y(){return transform.y;}
    float z(){return transform.z;}
    float pitch(){return transform.pitch;}
    float yaw(){return transform.yaw;}
    float roll(){return transform.roll;}

    glm::vec3 getPosition();
    glm::vec3 getRotation();
    glm::vec3 getScale();
    glm::vec3 getXAxis();
    glm::vec3 getYAxis();
    glm::vec3 getZAxis();
    glm::mat4 getRotationMatrix();

    void setX(float);
    void setY(float);
    void setZ(float);

    //algo obsoletas
    void setPitch(float);
    void setYaw(float);
    void setRoll(float);

    void rotateGlobalXAxis();
    void rotateGlobalYAxis(float);
    void rotateGlobalZAxis();

    void scaleX(float);
    void scaleY(float);
    void scaleZ(float);

    //nuevas funciones
    //estas funciones pretenden reemplazar las ambiguedades de las funciones anteriores
    void rotateLocal_X(float);
    void rotateLocal_Y(float);
    void rotateLocal_Z(float);
    void updatePitchYawRoll();
    void resetLocalAxles();
    void updateLocalAxles();

public:
    struct Transform
    {
        //position
        float x;
        float y;
        float z;
        //rotate
        float pitch;
        float yaw;
        float roll;
        //scale
        float scaleX;
        float scaleY;
        float scaleZ;
    } transform;

    struct LocalAxles
    {
        glm::vec3 xAxis;
        glm::vec3 yAxis;
        glm::vec3 zAxis;
    } localAxles;
    

};

#endif