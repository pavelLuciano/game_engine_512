#ifndef _MY_CAMERA_H
#define _MY_CAMERA_H
#include "Entity.h"
#include "IControlable.h"


class MyCamera: public Entity, IControlable
{
private:
    
    bool orthographic = false;
    float fov = 60.0f;

public:
    MyCamera();
    void setPerspective();
    void setOrthographic();
    void setProjection(bool);

    glm::mat4 getViewMat();
    glm::mat4 getProjectionMat();

    void processMouseInput(float, float);
    void processInput(GLFWwindow*, float) override;
    void move(glm::vec3) override;
};

#endif