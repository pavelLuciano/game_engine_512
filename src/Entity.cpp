#include "Entity.h"
#include <cmath>
#include <iostream>

Entity::Entity()
{
    transform = {0.0, 0.0, 0.0,
                 0.0, 0.0, 0.0,
                 1.0, 1.0, 1.0};
}
void Entity::setX(float x){transform._x = x;}
void Entity::setY(float y){transform._y = y;}
void Entity::setZ(float z){transform._z = z;}

void Entity::setPitch(float pitch)
{
    if (pitch < 0.0f) transform._pitch = 0.0f;
    else if (pitch > 360.0f) transform._pitch = std::fmod(transform._pitch, 360.0f);
    else transform._pitch = pitch;
}
void Entity::setYaw(float yaw)
{
    transform._yaw = std::fmod(yaw, 360.0f);
}
void Entity::setRoll(float roll)
{
    if (roll < 0.0f) transform._roll = 0.0f;
    else if (roll > 360.0f) transform._roll = 360.0;
    else transform._roll = roll;
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