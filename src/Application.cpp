#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include "imgui.h"
#include "implot.h"
#include "init_deps.h"
#include "engine512_gui.h"
#include "Box.h"
#include "Shape.h"
#include "MyShader.h"
#include "MyCamera.h"


/////////////////////////////////////////////////////////////////////////
//
//                          MAIN FUNCTION
//
/////////////////////////////////////////////////////////////////////////
int main()
{
    //crea la ventana e inicia las librerias necesarias
    // GLFW, GLEW, IMGUI, IMPLOT
    GLFWwindow* mi_ventana = initDepsAndCreateWin();
    if (!mi_ventana) return EXIT_FAILURE;

    //camara
    MyCamera camara;
    //figura dibujable

    Shape otra_caja("../resources/shapes/box.shape");
    //Shape triangulo("../resources/shapes/triangle.shape");
    //Box cajita;
    Shape cajita("../resources/shapes/box.shape");

    otra_caja.setX(1.0f);
    otra_caja.setY(1.0f);
    otra_caja.setZ(-10.0f);

    otra_caja.printVertex();
    cajita.printVertex();


    //shader
    MyShader mi_shader("../resources/shaders/vertex_shader.shader", "../resources/shaders/fragment_shader.shader");

    if (!mi_shader.isCompiled()) return EXIT_FAILURE;
    
    //bucle de ejecucion
    while (!glfwWindowShouldClose(mi_ventana))
    {
        
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();
        if (glfwGetWindowAttrib(mi_ventana, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }
        processInput(mi_ventana);
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //modificador del objeto caja
        mi_shader.setCamera(camara);
        //Engine512::entityMenu(&cajita, "Caja");
        //Engine512::cameraMenu(&camara);

        cajita.draw(mi_shader);
        otra_caja.draw(mi_shader);
        //triangulo.draw(mi_shader);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(mi_ventana);
    }
    
    glfwTerminate();
    return EXIT_SUCCESS;
}


int _main()
{
    //
    // GLFW & GLEW
    //
    if (!glfwInit())
    {
        std::cerr << "ERROR::NO_SE_PUDO_INICIAR_GLFW" << std::endl;
        return EXIT_FAILURE;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* mi_ventana = glfwCreateWindow(WIDTH, HEIGHT, "HolaMundo!", NULL, NULL);
    if (!mi_ventana)
    {
        std::cerr << "No se pudo crear la ventana" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    };
    glfwMakeContextCurrent(mi_ventana);
    glfwSwapInterval(1);
    glfwSetFramebufferSizeCallback(mi_ventana, framebuffer_size_callback);
    
    if (glewInit() != GLEW_OK) 
    {
        std::cerr << "ERROR::NO_SE_PUDO_INICIAR_GLEW" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }
    std::cout << "OpenGL iniciado correctamente\nVersion: " << glGetString(GL_VERSION) << std::endl;
    glEnable(GL_DEPTH_TEST);

    //
    // IMGUI & IMPLOT
    //
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
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


    int display_w, display_h;
    // Our state
    bool show_demo_window = true;
    bool show_another_window = false;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    while (!glfwWindowShouldClose(mi_ventana))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();
        if (glfwGetWindowAttrib(mi_ventana, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (show_demo_window)
            ImGui::ShowDemoWindow(&show_demo_window);

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            static float f = 0.0f;
            static int counter = 0;
            static bool open = true;

            ImGui::Begin("Hello, world!", &open , 0);                          // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
            ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
            ImGui::Checkbox("Another Window", &show_another_window);

            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }

        // 3. Show another simple window.
        if (show_another_window)
        {
            ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
            ImGui::Text("Hello from another window!");
            if (ImGui::Button("Close Me"))
                show_another_window = false;
            ImGui::End();
        }

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(mi_ventana, &display_w, &display_h);
        glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(mi_ventana);
    }

    printf("Hola Mundo!\n");
    return EXIT_SUCCESS;
}

