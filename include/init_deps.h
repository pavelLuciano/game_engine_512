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

struct mouseData
{
    float lastX = 600.0f / 2.0f;
    float lastY =  600.0f / 2.0f;
    bool firstMouse = true;
    bool newOffsets = false;

    float xOffset;
    float yOffset;

    bool hasUnprocesedOffsets()
    {
        if (newOffsets)
        {
            newOffsets = false;
            return true;
        }
        else return false;
    }
    
} mouse;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

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
    glfwSetCursorPosCallback(mi_ventana, mouse_callback);
    glfwSetScrollCallback(mi_ventana, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(mi_ventana, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    if (glewInit() != GLEW_OK) 
    {
        std::cerr << "ERROR::NO_SE_PUDO_INICIAR_GLEW" << std::endl;
        glfwTerminate();
        return NULL;
    }
    glViewport(0, 0, WIDTH*0.8,  HEIGHT);
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
    glViewport(0, 0, height,  height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    std::cout << "Mouse pos:" << xpos << " " << ypos << std::endl;
    if (mouse.firstMouse)
    {
        mouse.lastX = xpos;
        mouse.lastY = ypos;
        mouse.firstMouse = false;
    }

    mouse.xOffset = xpos - mouse.lastX;
    mouse.yOffset = mouse.lastY - ypos; // reversed since y-coordinates go from bottom to top

    mouse.lastX = xpos;
    mouse.lastY = ypos;
    std::cout << "offset :" << mouse.xOffset <<  " " << mouse.yOffset << std::endl;
    mouse.newOffsets = true;
}
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    //camera.ProcessMouseScroll(static_cast<float>(yoffset));
}