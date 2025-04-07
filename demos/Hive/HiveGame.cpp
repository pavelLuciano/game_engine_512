#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include "imgui.h"
#include "HiveEngine.h"
#include "Jugador.h"

int main()
{
    BeeHive::init();
    //SetupGame

    
    
    while (!glfwWindowShouldClose(BeeHive::window.self))
    {
        BeeHive::clock.updateFrame();
        glfwPollEvents();
        glfwPollEvents();
        if (glfwGetWindowAttrib(BeeHive::window.self, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }
        BeeHive::processInput();
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

    }


    BeeHive::terminate();
}