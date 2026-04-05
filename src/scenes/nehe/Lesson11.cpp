#include "Lesson11.hpp"

#include <metarender/core/AssetManager.hpp>
#include <metarender/core/Engine.hpp>
#include <metarender/input/InputManager.hpp>
#include <metarender/log/Log.hpp>
#include <metarender/platform/Window.hpp>
#include <metarender/renderer/IRenderer.hpp>

#include <glad/glad.h>
#include <imgui.h>
#include <math.h>

namespace metarender::scenes::nehe {

void Lesson11::onEnter() {
  m_texture = m_assetManager->loadTexture("assets/nehe/Tim.bmp");

  glBindTexture(GL_TEXTURE_2D, m_texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glEnable(GL_TEXTURE_2D);

  glPolygonMode(GL_BACK, GL_FILL);  // Back Face Is Filled In
  glPolygonMode(GL_FRONT, GL_LINE); // Front Face Is Drawn With Lines

  // Loop Through The X Plane
  for (int x = 0; x < 45; x++) {
    // Loop Through The Y Plane
    for (int y = 0; y < 45; y++) {
      // Apply The Wave To Our Mesh
      points[x][y][0] = float((x / 5.0f) - 4.5f);
      points[x][y][1] = float((y / 5.0f) - 4.5f);
      points[x][y][2] =
          float(sin((((x / 5.0f) * 40.0f) / 360.0f) * 3.141592654 * 2.0f));
    }
  }
}

void Lesson11::onUpdate(float deltaTime) {
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

void Lesson11::onRenderUI() {
  ImGui::Text("Speed");
  ImGui::SliderFloat("X", &m_xRotSpeed, -360, 360);
  ImGui::SliderFloat("Y", &m_yRotSpeed, -360, 360);
  ImGui::SliderFloat("Z", &m_zRotSpeed, -360, 360);
}

void Lesson11::onRender() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  m_renderer->perspective(45.0f, m_engine->getWindow().getAspectRatio(), 0.1f,
                          100.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  int x, y;
  float float_x, float_y, float_xb, float_yb;

  glTranslatef(0.0f, 0.0f, -17.0f); // Translate 12 Units Into The Screen

  glRotatef(m_xRot, 1.0f, 0.0f, 0.0f); // Rotate On The X Axis
  glRotatef(m_yRot, 0.0f, 1.0f, 0.0f); // Rotate On The Y Axis
  glRotatef(m_zRot, 0.0f, 0.0f, 1.0f); // Rotate On The Z Axis

  glBindTexture(GL_TEXTURE_2D, m_texture);

  glBegin(GL_QUADS);              // Start Drawing Our Quads
  for (x = 0; x < 44; x++) {      // Loop Through The X Plane (44 Points)
    for (y = 0; y < 44; y++) {    // Loop Through The Y Plane (44 Points)
      float_x = float(x) / 44.0f; // Create A Floating Point X Value
      float_y = float(y) / 44.0f; // Create A Floating Point Y Value
      float_xb =
          float(x + 1) / 44.0f; // Create A Floating Point Y Value+0.0227f
      float_yb =
          float(y + 1) / 44.0f; // Create A Floating Point Y Value+0.0227f

      glTexCoord2f(float_x, float_y); // First Texture Coordinate (Bottom Left)
      glVertex3f(points[x][y][0], points[x][y][1], points[x][y][2]);

      glTexCoord2f(float_x, float_yb); // Second Texture Coordinate (Top Left)
      glVertex3f(points[x][y + 1][0], points[x][y + 1][1], points[x][y + 1][2]);

      glTexCoord2f(float_xb, float_yb); // Third Texture Coordinate (Top Right)
      glVertex3f(points[x + 1][y + 1][0], points[x + 1][y + 1][1],
                 points[x + 1][y + 1][2]);

      glTexCoord2f(float_xb,
                   float_y); // Fourth Texture Coordinate (Bottom Right)
      glVertex3f(points[x + 1][y][0], points[x + 1][y][1], points[x + 1][y][2]);
    }
  }
  glEnd(); // Done Drawing The Quad Strip

  if (wiggle_count == 2) { // Used To Slow Down The Wave (Every 2nd Frame Only)
    for (y = 0; y < 45; y++) // Loop Through The Y Plane
    {
      hold = points[0][y][2];  // Store Current Value One Left Side Of Wave
      for (x = 0; x < 44; x++) // Loop Through The X Plane
      {
        // Current Wave Value Equals Value To The Right
        points[x][y][2] = points[x + 1][y][2];
      }
      points[44][y][2] = hold; // Last Value Becomes The Far Left Stored Value
    }
    wiggle_count = 0; // Set Counter Back To Zero
  }
  wiggle_count++; // Increase The Counter
}

} // namespace metarender::scenes::nehe
