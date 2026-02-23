#include "Lesson03.hpp"

#include <metarender/log/Log.hpp>
#include <metarender/renderer/IRenderer.hpp>
#include <metarender/core/Engine.hpp>
#include <metarender/platform/Window.hpp>

#include <glad/glad.h>
#include <imgui.h>

namespace metarender::scenes::nehe {

void Lesson03::onEnter() {
	p1 = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	p2 = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
	p3 = ImVec4(0.0f, 0.0f, 1.0f, 1.0f);
	quad = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
}

void Lesson03::onRenderUI() {
    ImGui::Text("p1");
    ImGui::ColorPicker4(
        "##p1",
        (float*)&p1,
        ImGuiColorEditFlags_PickerHueWheel |
        ImGuiColorEditFlags_NoSidePreview |
        ImGuiColorEditFlags_NoSmallPreview |
        ImGuiColorEditFlags_NoInputs |
        ImGuiColorEditFlags_NoAlpha
    );

    ImGui::Text("p2");
    ImGui::ColorPicker4(
        "##p2",
        (float*)&p2,
        ImGuiColorEditFlags_PickerHueWheel |
        ImGuiColorEditFlags_NoSidePreview |
        ImGuiColorEditFlags_NoSmallPreview |
        ImGuiColorEditFlags_NoInputs |
        ImGuiColorEditFlags_NoAlpha
    );

    ImGui::Text("p3");
    ImGui::ColorPicker4(
        "##p3",
        (float*)&p3,
        ImGuiColorEditFlags_PickerHueWheel |
        ImGuiColorEditFlags_NoSidePreview |
        ImGuiColorEditFlags_NoSmallPreview |
        ImGuiColorEditFlags_NoInputs |
        ImGuiColorEditFlags_NoAlpha
    );

    ImGui::Text("quad");
    ImGui::ColorPicker4(
        "##quad",
        (float*)&quad,
        ImGuiColorEditFlags_PickerHueWheel |
        ImGuiColorEditFlags_NoSidePreview |
        ImGuiColorEditFlags_NoSmallPreview |
        ImGuiColorEditFlags_NoInputs |
        ImGuiColorEditFlags_NoAlpha
    );
}

void Lesson03::onRender() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    m_renderer->perspective(45.0f, m_engine->getWindow().getAspectRatio(), 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glTranslatef(-1.5f, 0.0f, -6.0f);

    glBegin(GL_TRIANGLES);
    glColor3f(p1.x, p1.y, p1.z);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(p2.x, p2.y, p2.z);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glColor3f(p3.x, p3.y, p3.z);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();

    glTranslatef(3.0f, 0.0f, 0.0f);

    glColor3f(quad.x, quad.y, quad.z);
    glBegin(GL_QUADS);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glEnd();
}

}