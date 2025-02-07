#ifndef _I_CONTROLABLE_H
#define _I_CONTROLABLE_H
#include "GLFW/glfw3.h"

enum class Input
{
    FORDWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    uP,
    DOWN
};

class IControlable
{
    virtual void processInput(GLFWwindow*, float) = 0;
    virtual void move(glm::vec3) = 0;
};

#endif