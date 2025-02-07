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
void Entity::setX(float x){transform._x = x;}
void Entity::setY(float y){transform._y = y;}
void Entity::setZ(float z){transform._z = z;}

void Entity::setPitch(float pitch)
{
    transform._pitch = std::fmod(pitch, 360.0f);
    glm::mat4 aux_rot = glm::rotate(glm::mat4(1.0f), glm::radians(transform._pitch), xAxis);
    //no hay problema con la asignacion de un vec4 a un vec3
    yAxis = aux_rot * glm::vec4(yAxis, 1);
    zAxis = aux_rot * glm::vec4(zAxis, 1);
}
void Entity::setYaw(float yaw)
{
    transform._yaw = std::fmod(yaw, 360.0f);
    glm::mat4 aux_rot = glm::rotate(glm::mat4(1.0f), glm::radians(transform._yaw), yAxis);
    //no hay problema con la asignacion de un vec4 a un vec3
    xAxis = aux_rot * glm::vec4(xAxis, 1);
    zAxis = aux_rot * glm::vec4(zAxis, 1);
}
void Entity::setRoll(float roll)
{
    transform._roll = std::fmod(roll, 360.0f);
    glm::mat4 aux_rot = glm::rotate(glm::mat4(1.0f), glm::radians(transform._roll), zAxis);
    //no hay problema con la asignacion de un vec4 a un vec3
    xAxis = aux_rot * glm::vec4(xAxis, 1);
    yAxis = aux_rot * glm::vec4(yAxis, 1);
}


void Entity::rotateGlobalXAxis()
{

}
void Entity::rotateGlobalYAxis(float deg)
{
    glm::mat4 aux_rot = glm::rotate(glm::mat4(1.0f), glm::radians(deg), glm::vec3(0,1,0));
    xAxis = aux_rot * glm::vec4(xAxis, 1);
    yAxis = aux_rot * glm::vec4(yAxis, 1);
    zAxis = aux_rot * glm::vec4(zAxis, 1);

    transform._yaw   = glm::degrees(std::asin(-xAxis[2]));
    transform._pitch = glm::degrees(std::atan2(yAxis[2],zAxis[2]));
    transform._roll  = glm::degrees(std::atan2(xAxis[1],xAxis[0]));
}
void Entity::rotateGlobalZAxis()
{

}

void Entity::scaleX(float scaleX)
{
    transform._scaleX = scaleX;
}
void Entity::scaleY(float scaleY)
{
    transform._scaleY = scaleY;
}
void Entity::scaleZ(float scaleZ)
{
    transform._scaleZ = scaleZ;
}
glm::vec3 Entity::getPosition()
{
    return glm::vec3(transform._x, transform._y, transform._z);
}
glm::vec3 Entity::getRotation()
{
    return glm::vec3(transform._pitch, transform._yaw, transform._roll);
}
glm::vec3 Entity::getScale()
{
    return glm::vec3(transform._scaleX, transform._scaleY, transform._scaleZ);
}
glm::vec3 Entity::getXAxis(){return xAxis;}
glm::vec3 Entity::getYAxis(){return yAxis;}
glm::vec3 Entity::getZAxis(){return zAxis;}

void Entity::resetLocalAxles()
{
    xAxis = glm::vec3(1,0,0);
    yAxis = glm::vec3(0,1,0);
    zAxis = glm::vec3(0,0,1);
}