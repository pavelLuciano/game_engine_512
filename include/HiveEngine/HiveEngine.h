#pragma once

#ifndef _HIVE_ENGINE_H
#define _HIVE_ENGINE_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include "imgui.h"
#include "implot.h"
#include "Entity.h"
#include "MyCamera.h"
#include <iostream>
#include <string>


namespace BeeHive
{
    //Callbacks
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    //ESTRUCTURAS
    struct Window
    {
        GLFWwindow* self;
        int height = 600;
        int width = 800;
        int viewport_width = 600;
        int viewport_heigt = 600;
        int vieport_x = 0;
        int viewport_y = 0;

        void viewportUpdate()
        {
            viewport_heigt = height;
            viewport_width = height;
        }
        void setWindowSize(int _width, int _height)
        {
            height = _height;
            width = _width;
            viewportUpdate();
        }
    } window;
    struct Clock
    {
        float deltaTime = 0.0f;
        float lastFrame = 0.0f;

        void updateFrame()
        {
            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;
        }
    } clock;
    struct MouseData
    {
        float lastX = window.viewport_heigt / 2.0f;
        float lastY =  window.viewport_heigt / 2.0f;
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
    
    //MENUES
    void cameraMenu(MyCamera* cam, std::string label = "Camara")
    {
        if (ImGui::TreeNode(label.c_str()))
        {
            ImGui::SeparatorText("Transform");
            ImGui::InputFloat3("Position", &(cam->transform.x));
            ImGui::InputFloat3("Rotation", &(cam->transform.pitch));
            ImGui::InputFloat3("Scale", &(cam->transform.scaleX));
            ImGui::Spacing();
            ImGui::TreePop();
        }

    }
    void entityMenu(Entity* entity, std::string label = "Entity")
    {
        if (ImGui::TreeNode(label.c_str()))
        {
            ImGui::SeparatorText("Transform");
            ImGui::InputFloat3("Position", &(entity->transform.x));
            ImGui::InputFloat3("Rotation", &(entity->transform.pitch));
            ImGui::InputFloat3("Scale", &(entity->transform.scaleX));
            ImGui::Spacing();
            ImGui::TreePop();
        }
    }

    //SETUPS
    bool init()
    {
        //
        // GLFW & GLEW
        //
        if (!glfwInit())
        {
            std::cerr << "ERROR::NO_SE_PUDO_INICIAR_GLFW" << std::endl;
            return false;
        }
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        window.self = glfwCreateWindow(window.width, window.height, "HolaMundo!", NULL, NULL);
        if (!window.self)
        {
            std::cerr << "No se pudo crear la ventana" << std::endl;
            glfwTerminate();
            return false;
        };
        glfwMakeContextCurrent(window.self);
        glfwSwapInterval(1);
        glfwSetFramebufferSizeCallback(window.self, framebuffer_size_callback);
        glfwSetCursorPosCallback(window.self, mouse_callback);
        glfwSetScrollCallback(window.self, scroll_callback);

        // tell GLFW to capture our mouse
        glfwSetInputMode(window.self, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        
        if (glewInit() != GLEW_OK) 
        {
            std::cerr << "ERROR::NO_SE_PUDO_INICIAR_GLEW" << std::endl;
            glfwTerminate();
            return false;
        }
        glViewport(window.vieport_x, window.vieport_x,
                   window.viewport_width , window.viewport_heigt);
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
        ImGui_ImplGlfw_InitForOpenGL(window.self, true);
        ImGui_ImplOpenGL3_Init();
        return true;
    }

    bool terminate()
    {
        // Cerrar ImGui y ImPlot
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();

        // Cerrar GLFW
        glfwDestroyWindow(window.self);  // `window` es el puntero a tu ventana GLFW
        glfwTerminate();
        return true;
    }

    //Callbacks
    void framebuffer_size_callback(GLFWwindow* _win, int width, int height)
    {
        // make sure the viewport matches the new window dimensions; note that width and 
        // height will be significantly larger than specified on retina displays.
        window.setWindowSize(width, height);
        glViewport(window.vieport_x, window.vieport_x,
                   window.viewport_width , window.viewport_heigt);
    }
    void mouse_callback(GLFWwindow* _win, double xposIn, double yposIn)
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

    }
    void processInput()
    {
        if (glfwGetKey(window.self, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window.self, true);
    }



};

#endif