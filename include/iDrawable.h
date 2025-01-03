#ifndef _I_DRAWABLE_H
#define _I_DRAWABLE_H
#include "myShader.h"

class IDrawable
{
public:
    virtual void draw(MyShader) = 0;  // Funcion virtual pura
};

#endif