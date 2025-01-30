#ifndef _MY_CAMERA_H
#define _MY_CAMERA_H
#include "Entity.h"


class MyCamera: public Entity
{
private:
    
    bool orthographic = false;
    float fov = 45.0f;


public:
    MyCamera();
    void setPerspective();
    void setOrthographic();

    glm::mat4 getViewMat();
    glm::mat4 getProjectionMat();

};

#endif