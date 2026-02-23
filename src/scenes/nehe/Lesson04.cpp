#include "Lesson04.hpp"

#include <metarender/log/Log.hpp>
#include <metarender/renderer/IRenderer.hpp>
#include <metarender/core/Engine.hpp>
#include <metarender/platform/Window.hpp>

#include <glad/glad.h>
#include <imgui.h>

namespace metarender::scenes::nehe {

void Lesson04::onEnter() {
    m_triangleRotation = 0.0f;
    m_quadRotation = 0.0f;
}

void Lesson04::onUpdate(float deltaTime) {
    m_triangleRotation += m_rotationSpeed * deltaTime;
    m_quadRotation -= m_rotationSpeed * deltaTime;

    if (m_triangleRotation > 360.0f) m_triangleRotation -= 360.0f;
    if (m_quadRotation < -360.0f) m_quadRotation += 360.0f;
}

void Lesson04::onRenderUI() {
    ImGui::Text("Speed");
    ImGui::SliderFloat("##speed", &m_rotationSpeed, 0, 360);
}

void Lesson04::onRender() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    m_renderer->perspective(45.0f, m_engine->getWindow().getAspectRatio(), 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();
    glTranslatef(-1.5f, 0.0f, -6.0f);
    glRotatef(m_triangleRotation, 0.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glEnd();

	glLoadIdentity();
    glTranslatef(1.5f, 0.0f, -6.0f);
    glRotatef(m_quadRotation, 1.0f, 0.0f, 0.0f);

    glColor3f(0.5f, 0.5f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(-1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glEnd();
}

}