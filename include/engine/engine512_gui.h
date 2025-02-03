#ifndef _ENGINE512_GUI_H
#define _ENGINE512_GUI_H

#include "Entity.h"
#include "MyCamera.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"
#include "imgui.h"

#include <string>

namespace Engine512
{
    void entityMenu(Entity* e, std::string label = "Entity")
    {
        static float pos[3] = { 0.0f, 0.0f, 0.0f };
        static float rot[3] = { 0.0f, 0.0f, 0.0f };
        static float scale[3] = {1.0f, 1.0f, 1.0f};
        
        ImGui::Begin(label.c_str());
        ImGui::InputFloat3("Position", pos);
        ImGui::InputFloat3("Rotation", rot);
        ImGui::InputFloat3("Scale", scale);
        e->setX(pos[0]);
        e->setY(pos[1]);
        e->setZ(pos[2]);
        e->setPitch(rot[0]);
        e->setYaw(45.0f*glfwGetTime());
        e->setRoll(rot[2]);
        e->scaleX(scale[0]);
        e->scaleY(scale[1]);
        e->scaleZ(scale[2]);
        ImGui::End();
    }

    void cameraMenu(MyCamera* cam, std::string label = "Camera")
    {
        static float pos[3] = { 0.0f, 0.0f, 0.0f };
        static float rot[3] = { 0.0f, 0.0f, 0.0f };
        static bool ortho = false;
        ImGui::Begin(label.c_str());
        ImGui::InputFloat3("Position", pos);
        ImGui::InputFloat3("Rotation", rot);
        ImGui::Checkbox("orthogonal", &ortho);
        cam->setX(pos[0]);
        cam->setY(pos[1]);
        cam->setZ(pos[2]);
        cam->setPitch(rot[0]);
        cam->setYaw(rot[1]);
        cam->setRoll(rot[2]);
        cam->setProjection(ortho);
        ImGui::End();
    }
}

#endif