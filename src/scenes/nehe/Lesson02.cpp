#include "Lesson02.hpp"

#include <metarender/log/Log.hpp>
#include <metarender/renderer/IRenderer.hpp>
#include <metarender/core/Engine.hpp>
#include <metarender/platform/Window.hpp>

#include <glad/glad.h>
#include <imgui.h>

namespace metarender::scenes::nehe {


void Lesson02::onEnter() {
	m_triX = -1.5f;
	m_triY = 0.0f;
	m_triZ = -6.0f;
	m_quadX = 3.0f;
	m_quadY = 0.0f;
	m_quadZ = 0.0f;
}

void Lesson02::onRenderUI() {
    ImGui::Text("Transform");

    if (ImGui::CollapsingHeader("Triangle", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::PushID("Triangle");

        ImGui::DragFloat("X", &m_triX, 0.1f);
        ImGui::DragFloat("Y", &m_triY, 0.1f);
        ImGui::DragFloat("Z", &m_triZ, 0.1f);

        if (ImGui::Button("Reset")) {
            m_triX = -1.5f;
            m_triY = 0.0f;
            m_triZ = -6.0f;
        }

        ImGui::PopID();
    }

    if (ImGui::CollapsingHeader("Quad", ImGuiTreeNodeFlags_DefaultOpen)) {
        ImGui::PushID("Quad");

        ImGui::DragFloat("X", &m_quadX, 0.1f);
        ImGui::DragFloat("Y", &m_quadY, 0.1f);
        ImGui::DragFloat("Z", &m_quadZ, 0.1f);

        if (ImGui::Button("Reset")) {
            m_quadX = 3.0f;
            m_quadY = 0.0f;
            m_quadZ = 0.0f;
        }

        ImGui::PopID();
    }
}

void Lesson02::onRender() {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    m_renderer->perspective(45.0f, m_engine->getWindow().getAspectRatio(), 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glTranslatef(m_triX, m_triY, m_triZ);

    glBegin(GL_TRIANGLES);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();

    glTranslatef(m_quadX, m_quadY, m_quadZ);

    glBegin(GL_QUADS);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glEnd();
}

}