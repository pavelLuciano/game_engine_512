#ifndef _I_DRAWABLE_H
#define _I_DRAWABLE_H
#include "MyShader.h"

class IDrawable
{
public:
    virtual void draw(MyShader&) = 0;  // Funcion virtual pura
    virtual void draw() = 0;
};

#endif