#ifndef _ENTITY_H
#define _ENTITY_H

#include "iDrawable.h"
#include <vector>

class Entity: public IDrawable
{
public:
    Entity();
    ~Entity();

    double x(){return transform._x;}
    double y(){return transform._y;}
    double z(){return transform._z;}

private:
    struct Transform
    {
        double _x;
        double _y;
        double _z;
    } transform;

    void setX(double x){transform._x = x;}
    void setY(double y){transform._y = y;}
    void setZ(double z){transform._z = z;}
};

#endif