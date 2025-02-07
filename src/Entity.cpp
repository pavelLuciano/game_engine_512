#include "Entity.h"
#include <cmath>
#include <iostream>

Entity::Entity()
{
    transform = {0.0, 0.0, 0.0,
                 0.0, 0.0, 0.0,
                 1.0, 1.0, 1.0};
    resetLocalAxles();
}
void Entity::setX(float x){transform.x = x;}
void Entity::setY(float y){transform.y = y;}
void Entity::setZ(float z){transform.z = z;}

void Entity::setPitch(float pitch)
{
    transform.pitch = std::fmod(pitch, 360.0f);
    glm::mat4 aux_rot = glm::rotate(glm::mat4(1.0f), glm::radians(transform.pitch), getXAxis());
    //no hay problema con la asignacion de un vec4 a un vec3
    localAxles.yAxis = aux_rot * glm::vec4(getYAxis(), 1);
    localAxles.zAxis = aux_rot * glm::vec4(getZAxis(), 1);
}
void Entity::setYaw(float yaw)
{
    transform.yaw = std::fmod(yaw, 360.0f);
    glm::mat4 aux_rot = glm::rotate(glm::mat4(1.0f), glm::radians(transform.yaw), getYAxis());
    //no hay problema con la asignacion de un vec4 a un vec3
    localAxles.xAxis = aux_rot * glm::vec4(getXAxis(), 1);
    localAxles.zAxis = aux_rot * glm::vec4(getZAxis(), 1);
}
void Entity::setRoll(float roll)
{
    transform.roll = std::fmod(roll, 360.0f);
    glm::mat4 aux_rot = glm::rotate(glm::mat4(1.0f), glm::radians(transform.roll), getZAxis());
    //no hay problema con la asignacion de un vec4 a un vec3
    localAxles.xAxis = aux_rot * glm::vec4(getXAxis(), 1);
    localAxles.yAxis = aux_rot * glm::vec4(getYAxis(), 1);
}


void Entity::rotateGlobalXAxis()
{

}
void Entity::rotateGlobalYAxis(float deg)
{
    glm::mat4 aux_rot = glm::rotate(glm::mat4(1.0f), glm::radians(deg), glm::vec3(0,1,0));
    localAxles.xAxis = aux_rot * glm::vec4(getXAxis(), 1);
    localAxles.yAxis = aux_rot * glm::vec4(getYAxis(), 1);
    localAxles.zAxis = aux_rot * glm::vec4(getZAxis(), 1);

    updatePitchYawRoll();
}
void Entity::rotateGlobalZAxis()
{

}

void Entity::scaleX(float scaleX)
{
    transform.scaleX = scaleX;
}
void Entity::scaleY(float scaleY)
{
    transform.scaleY = scaleY;
}
void Entity::scaleZ(float scaleZ)
{
    transform.scaleZ = scaleZ;
}
glm::vec3 Entity::getPosition()
{
    return glm::vec3(transform.x, transform.y, transform.z);
}
glm::vec3 Entity::getRotation()
{
    return glm::vec3(transform.pitch, transform.yaw, transform.roll);
}
glm::vec3 Entity::getScale()
{
    return glm::vec3(transform.scaleX, transform.scaleY, transform.scaleZ);
}
glm::vec3 Entity::getXAxis(){return localAxles.xAxis;}
glm::vec3 Entity::getYAxis(){return localAxles.yAxis;}
glm::vec3 Entity::getZAxis(){return localAxles.zAxis;}

void Entity::resetLocalAxles()
{
    localAxles.xAxis = glm::vec3(1,0,0);
    localAxles.yAxis = glm::vec3(0,1,0);
    localAxles.zAxis = glm::vec3(0,0,1);
}

void Entity::rotateLocal_X(float deg)
{
    glm::mat4 aux_rot = glm::rotate(glm::mat4(1.0f), glm::radians(deg), getXAxis());
    //no hay problema con la asignacion de un vec4 a un vec3
    localAxles.yAxis = aux_rot * glm::vec4(getYAxis(), 1);
    localAxles.zAxis = aux_rot * glm::vec4(getZAxis(), 1);
    updatePitchYawRoll();
}

void Entity::updatePitchYawRoll()
{
    //esta funcion asume que la matriz de rotacion utilizada es EulerXYZ
    transform.yaw   = glm::degrees(std::asin(-getXAxis()[2]));
    transform.pitch = glm::degrees(std::atan2(getYAxis()[2],getZAxis()[2]));
    transform.roll  = glm::degrees(std::atan2(getXAxis()[1],getXAxis()[0]));
}

void Entity::updateLocalAxles()
{
    //resetLocalAxles();
    glm::mat4 rotation = getRotationMatrix();
    localAxles.xAxis = rotation * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
    localAxles.yAxis = rotation * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
    localAxles.zAxis = rotation * glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
}

glm::mat4 Entity::getRotationMatrix()
{
    return glm::rotate(glm::mat4(1.0f), glm::radians(transform.roll), getZAxis()) *
           glm::rotate(glm::mat4(1.0f), glm::radians(transform.yaw), getYAxis())  *
           glm::rotate(glm::mat4(1.0f), glm::radians(transform.pitch), getXAxis());
}