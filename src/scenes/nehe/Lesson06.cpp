#include "Lesson06.hpp"

#include <metarender/core/AssetManager.hpp>
#include <metarender/core/Engine.hpp>
#include <metarender/log/Log.hpp>
#include <metarender/platform/Window.hpp>
#include <metarender/renderer/IRenderer.hpp>

#include <glad/glad.h>
#include <imgui.h>

namespace metarender::scenes::nehe {

void Lesson06::onEnter() {
  m_texture = m_assetManager->loadTexture("assets/nehe/NeHe.bmp");

  glBindTexture(GL_TEXTURE_2D, m_texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glEnable(GL_TEXTURE_2D);
}

void Lesson06::onUpdate(float deltaTime) {
  m_xRot += m_xRotSpeed * deltaTime;
  m_yRot += m_yRotSpeed * deltaTime;
  m_zRot += m_zRotSpeed * deltaTime;

  if (m_xRot > 360.0f)
    m_xRot -= 360.0f;
  if (m_yRot > 360.0f)
    m_yRot -= 360.0f;
  if (m_zRot > 360.0f)
    m_zRot -= 360.0f;
  if (m_xRot < -360.0f)
    m_xRot = 360.0f;
  if (m_yRot < -360.0f)
    m_yRot = 360.0f;
  if (m_zRot < -360.0f)
    m_zRot = 360.0f;
}

void Lesson06::onRenderUI() {
  ImGui::Text("Speed");
  ImGui::SliderFloat("X", &m_xRotSpeed, -360, 360);
  ImGui::SliderFloat("Y", &m_yRotSpeed, -360, 360);
  ImGui::SliderFloat("Z", &m_zRotSpeed, -360, 360);
}

void Lesson06::onRender() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  m_renderer->perspective(45.0f, m_engine->getWindow().getAspectRatio(), 0.1f,
                          100.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glTranslatef(0.0f, 0.0f, -5.0f);
  glRotatef(m_xRot, 1.0f, 0.0f, 0.0f); // Rotate On The X Axis
  glRotatef(m_yRot, 0.0f, 1.0f, 0.0f); // Rotate On The Y Axis
  glRotatef(m_zRot, 0.0f, 0.0f, 1.0f); // Rotate On The Z Axis

  glBindTexture(GL_TEXTURE_2D, m_texture);
  glBegin(GL_QUADS);
  // Front Face
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f); // Bottom Left Of The Texture and Quad
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, 1.0f); // Bottom Right Of The Texture and Quad
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f); // Top Right Of The Texture and Quad
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f); // Top Left Of The Texture and Quad
  // Back Face
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f); // Bottom Right Of The Texture and Quad
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f); // Top Right Of The Texture and Quad
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f); // Top Left Of The Texture and Quad
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, -1.0f); // Bottom Left Of The Texture and Quad
  // Top Face
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f); // Top Left Of The Texture and Quad
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f); // Bottom Left Of The Texture and Quad
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(1.0f, 1.0f, 1.0f); // Bottom Right Of The Texture and Quad
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f); // Top Right Of The Texture and Quad
  // Bottom Face
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f); // Top Right Of The Texture and Quad
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(1.0f, -1.0f, -1.0f); // Top Left Of The Texture and Quad
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, 1.0f); // Bottom Left Of The Texture and Quad
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f); // Bottom Right Of The Texture and Quad
  // Right face
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, -1.0f); // Bottom Right Of The Texture and Quad
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f); // Top Right Of The Texture and Quad
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f); // Top Left Of The Texture and Quad
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, 1.0f); // Bottom Left Of The Texture and Quad
  // Left Face
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f); // Bottom Left Of The Texture and Quad
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f); // Bottom Right Of The Texture and Quad
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f); // Top Right Of The Texture and Quad
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f); // Top Left Of The Texture and Quad
  glEnd();
}

} // namespace metarender::scenes::nehe
