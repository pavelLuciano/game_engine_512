#include "MyCamera.h"

MyCamera::MyCamera()
{
    setZ(3.0f);
}

void MyCamera::setPerspective(){orthographic = false;}
void MyCamera::setOrthographic(){orthographic = true;}

//modificar
glm::mat4 MyCamera::getViewMat()
{
    return glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
}
glm::mat4 MyCamera::getProjectionMat()
{
    if (orthographic) return glm::ortho(0.0f, 600.0f, 0.0f, 600.0f, 0.1f, 100.0f);
    else return glm::perspective(glm::radians(fov), 600.0f / 600.0f, 0.1f, 100.0f);
}