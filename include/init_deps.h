#pragma once 
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include "imgui.h"
#include "implot.h"
#include <iostream>

//ENV VARS
#define HEIGHT 600
#define WIDTH  800

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

inline GLFWwindow* initDepsAndCreateWin()
{
    //
    // GLFW & GLEW
    //
    if (!glfwInit())
    {
        std::cerr << "ERROR::NO_SE_PUDO_INICIAR_GLFW" << std::endl;
        return NULL;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* mi_ventana = glfwCreateWindow(WIDTH, HEIGHT, "HolaMundo!", NULL, NULL);
    if (!mi_ventana)
    {
        std::cerr << "No se pudo crear la ventana" << std::endl;
        glfwTerminate();
        return NULL;
    };
    glfwMakeContextCurrent(mi_ventana);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(mi_ventana, framebuffer_size_callback);
    
    if (glewInit() != GLEW_OK) 
    {
        std::cerr << "ERROR::NO_SE_PUDO_INICIAR_GLEW" << std::endl;
        glfwTerminate();
        return NULL;
    }
    std::cout << "OpenGL iniciado correctamente\nVersion: " << glGetString(GL_VERSION) << std::endl;
    glEnable(GL_DEPTH_TEST);

    //
    // IMGUI & IMPLOT
    //
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImPlot::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch
    //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // IF using Multi-Viewport (?)

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(mi_ventana, true);
    ImGui_ImplOpenGL3_Init();
    return mi_ventana;
}

inline void render()
{
    
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width*0.8,  height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
