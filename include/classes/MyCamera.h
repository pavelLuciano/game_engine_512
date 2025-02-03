#ifndef _MY_CAMERA_H
#define _MY_CAMERA_H
#include "Entity.h"


class MyCamera: public Entity
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

};

#endif