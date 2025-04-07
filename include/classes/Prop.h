#ifndef _PROP_H
#define _PROP_H
#include "Entity.h"
#include "IDrawable.h"

class Prop: Entity, IDrawable
{
public:

    

    void update() override;
    void draw() override;
    void draw(MyShader&) override;

    
};

#endif