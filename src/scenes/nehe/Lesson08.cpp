#include "Lesson08.hpp"

#include <metarender/core/AssetManager.hpp>
#include <metarender/core/Engine.hpp>
#include <metarender/log/Log.hpp>
#include <metarender/platform/Window.hpp>
#include <metarender/renderer/IRenderer.hpp>

#include <glad/glad.h>
#include <imgui.h>

namespace metarender::scenes::nehe {

enum class TextureFilter { Nearest = 0, Linear = 1, Mipmap = 2 };

static const char *filterLabels[] = {"Nearest", "Linear", "Mipmap"};

void Lesson08::onEnter() {
  TextureData data = m_assetManager->loadTextureData("assets/nehe/Glass.bmp");

  glEnable(GL_TEXTURE_2D);
  glGenTextures(3, m_textures.data());

  // --- Texture 0: Nearest ---
  glBindTexture(GL_TEXTURE_2D, m_textures.at(0));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, data.width, data.height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, data.data);

  // --- Texture 1: Linear ---
  glBindTexture(GL_TEXTURE_2D, m_textures.at(1));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, data.width, data.height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, data.data);

  // --- Texture 2: Mipmapped ---
  glBindTexture(GL_TEXTURE_2D, m_textures.at(2));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_NEAREST);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, data.width, data.height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, data.data);
  glGenerateMipmap(GL_TEXTURE_2D);

  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHTING);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE);

  m_enableBlending = true;
}

void Lesson08::onUpdate(float deltaTime) {
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

void Lesson08::onRenderUI() {
  ImGui::Text("Speed");
  ImGui::SliderFloat("X", &m_xRotSpeed, -360, 360);
  ImGui::SliderFloat("Y", &m_yRotSpeed, -360, 360);
  ImGui::SliderFloat("Z", &m_zRotSpeed, -360, 360);

  if (ImGui::Button("Stop")) {
    m_xRotSpeed = 0.0f;
    m_yRotSpeed = 0.0f;
    m_zRotSpeed = 0.0f;
  }

  ImGui::Separator();
  ImGui::Text("Texture Filtering");
  if (ImGui::Combo("##filter", &m_currentFilter, filterLabels,
                   IM_ARRAYSIZE(filterLabels))) {
  }

  ImGui::SeparatorText("Enable blending");
  ImGui::Checkbox("##enable_blending", &m_enableBlending);
}

void Lesson08::onRender() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  m_renderer->perspective(45.0f, m_engine->getWindow().getAspectRatio(), 0.1f,
                          100.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  if (m_enableBlending) {
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);
  } else {
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
  }

  glLightfv(GL_LIGHT1, GL_AMBIENT, m_lightAmbient.data());
  glLightfv(GL_LIGHT1, GL_DIFFUSE, m_lightDiffuse.data());
  glLightfv(GL_LIGHT1, GL_POSITION, m_lightPosition.data());

  glTranslatef(0.0f, 0.0f, -5.0f);

  glRotatef(m_xRot, 1.0f, 0.0f, 0.0f);
  glRotatef(m_yRot, 0.0f, 1.0f, 0.0f);
  glRotatef(m_zRot, 0.0f, 0.0f, 1.0f);

  glBindTexture(GL_TEXTURE_2D, m_textures.at(m_currentFilter));
  glColor4f(1.0f, 1.0f, 1.0f, 0.5f);

  glBegin(GL_QUADS);
  // Front Face
  glNormal3f(0.0f, 0.0f, 1.0f); // Normal Pointing Towards Viewer
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f); // Point 1 (Front)
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, 1.0f); // Point 2 (Front)
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f); // Point 3 (Front)
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f); // Point 4 (Front)
  // Back Face
  glNormal3f(0.0f, 0.0f, -1.0f); // Normal Pointing Away From Viewer
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f); // Point 1 (Back)
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f); // Point 2 (Back)
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f); // Point 3 (Back)
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, -1.0f); // Point 4 (Back)
  // Top Face
  glNormal3f(0.0f, 1.0f, 0.0f); // Normal Pointing Up
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f); // Point 1 (Top)
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f); // Point 2 (Top)
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(1.0f, 1.0f, 1.0f); // Point 3 (Top)
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f); // Point 4 (Top)
  // Bottom Face
  glNormal3f(0.0f, -1.0f, 0.0f); // Normal Pointing Down
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f); // Point 1 (Bottom)
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(1.0f, -1.0f, -1.0f); // Point 2 (Bottom)
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, 1.0f); // Point 3 (Bottom)
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f); // Point 4 (Bottom)
  // Right face
  glNormal3f(1.0f, 0.0f, 0.0f); // Normal Pointing Right
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, -1.0f); // Point 1 (Right)
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, -1.0f); // Point 2 (Right)
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(1.0f, 1.0f, 1.0f); // Point 3 (Right)
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(1.0f, -1.0f, 1.0f); // Point 4 (Right)
  // Left Face
  glNormal3f(-1.0f, 0.0f, 0.0f); // Normal Pointing Left
  glTexCoord2f(0.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, -1.0f); // Point 1 (Left)
  glTexCoord2f(1.0f, 0.0f);
  glVertex3f(-1.0f, -1.0f, 1.0f); // Point 2 (Left)
  glTexCoord2f(1.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, 1.0f); // Point 3 (Left)
  glTexCoord2f(0.0f, 1.0f);
  glVertex3f(-1.0f, 1.0f, -1.0f); // Point 4 (Left)
  glEnd();
}

} // namespace metarender::scenes::nehe
