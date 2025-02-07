#include "MyCamera.h"
#include <cmath>
#include <iostream>

MyCamera::MyCamera()
{
    setX(-1.0f);
    setZ(5.0f);
}

void MyCamera::setPerspective(){orthographic = false;}
void MyCamera::setOrthographic(){orthographic = true;}
void MyCamera::setProjection(bool b)
{
    if (b) setOrthographic();
    else setPerspective();
}

//modificar
glm::mat4 MyCamera::getViewMat()
{
    //return glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f));
    return glm::lookAt(getPosition(), getPosition() - zAxis, yAxis);
}
glm::mat4 MyCamera::getProjectionMat()
{
    if (orthographic) return glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
    else return glm::perspective(glm::radians(fov), 600.0f / 600.0f, 0.1f, 100.0f);
}

void MyCamera::processMouseInput(float xoffset, float yoffset)
{
    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    setPitch(yoffset);
    
}


void MyCamera::processInput(GLFWwindow* window,float deltaTime)
{
    glm::vec3 direction = glm::vec3(0.0f);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        direction += -zAxis;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        direction += zAxis;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        direction -= xAxis; 
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        direction += xAxis;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        direction += yAxis; 
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        direction -= yAxis;

    if (direction != glm::vec3(0.0f))
    {
        direction = glm::normalize(direction);
        glm::vec3 translation = deltaTime * 2.0f * direction;
        move(translation);
    }
}

void MyCamera::move(glm::vec3 move_vec)
{
    transform._x += move_vec[0];
    transform._y += move_vec[1];
    transform._z += move_vec[2];
}
