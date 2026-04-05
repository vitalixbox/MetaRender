#include "Lesson15.hpp"

#include <metarender/core/AssetManager.hpp>
#include <metarender/core/Engine.hpp>
#include <metarender/input/InputManager.hpp>
#include <metarender/log/Log.hpp>
#include <metarender/platform/Window.hpp>
#include <metarender/renderer/IRenderer.hpp>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <Windows.h>
#include <glad/glad.h>
#include <imgui.h>

namespace metarender::scenes::nehe {

void Lesson15::onEnter() {
  TextureData data = m_assetManager->loadTextureData("assets/nehe/Lights.bmp");

  glEnable(GL_TEXTURE_2D);
  glGenTextures(1, &m_texture);

  glBindTexture(GL_TEXTURE_2D, m_texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, data.width, data.height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, data.data);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
                  GL_LINEAR_MIPMAP_NEAREST);
  glGenerateMipmap(GL_TEXTURE_2D);

  BuildFont();

  glEnable(GL_LIGHT0);
  glEnable(GL_LIGHTING);
}

void Lesson15::onUpdate(float deltaTime) {}

void Lesson15::onRenderUI() {
  ImGui::Text("Rotate Scene");
  ImGui::SliderFloat("X", &xRot, -360, 360);
  ImGui::SliderFloat("Y", &yRot, -360, 360);
  ImGui::SliderFloat("Z", &zRot, -360, 360);
}

void Lesson15::BuildFont() {
  HFONT font; // Windows Font ID

  GLFWwindow *window = m_engine->getWindow().getNativeHandle();
  HWND hwnd = glfwGetWin32Window(window);
  HDC hDC = GetDC(hwnd);

  base = glGenLists(256);                        // Storage For 256 Characters
  font = CreateFont(-12,                         // Height Of Font
                    0,                           // Width Of Font
                    0,                           // Angle Of Escapement
                    0,                           // Orientation Angle
                    FW_BOLD,                     // Font Weight
                    FALSE,                       // Italic
                    FALSE,                       // Underline
                    FALSE,                       // Strikeout
                    SYMBOL_CHARSET,              // Character Set Identifier
                    OUT_TT_PRECIS,               // Output Precision
                    CLIP_DEFAULT_PRECIS,         // Clipping Precision
                    ANTIALIASED_QUALITY,         // Output Quality
                    FF_DONTCARE | DEFAULT_PITCH, // Family And Pitch
                    "Wingdings");

  SelectObject(hDC, font); // Selects The Font We Created
  wglUseFontOutlines(hDC, 0, 255, base, 0.0f, 0.2f, WGL_FONT_POLYGONS, gmf);
}

void Lesson15::KillFont() {
  glDeleteLists(base, 256); // Delete All 256 Characters
}

void Lesson15::glPrint(const char *fmt, ...) {
  float length = 0; // Used To Find The Length Of The Text
  char text[256];   // Holds Our String
  va_list ap;       // Pointer To List Of Arguments

  if (fmt == nullptr) {
    return;
  }

  va_start(ap, fmt); // Parses The String For Variables
  vsprintf_s(text, sizeof(text), fmt,
             ap); // And Converts Symbols To Actual Numbers
  va_end(ap);     // Results Are Stored In Text

  for (unsigned int loop = 0; loop < (strlen(text));
       loop++) { // Loop To Find Text Length
    length +=
        gmf[text[loop]].gmfCellIncX; // Increase Length By Each Characters Width
  }
  glTranslatef(-length / 2, 0.0f, 0.0f); // Center Our Text On The Screen
  glPushAttrib(GL_LIST_BIT);             // Pushes The Display List Bits
  glListBase(base);                      // Sets The Base Character to 0
  glCallLists(strlen(text), GL_UNSIGNED_BYTE,
              text); // Draws The Display List Text
  glPopAttrib();     // Pops The Display List Bits
}

void Lesson15::onRender() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  m_renderer->perspective(45.0f, m_engine->getWindow().getAspectRatio(), 0.1f,
                          100.0f);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
  glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
  glEnable(GL_TEXTURE_GEN_S);
  glEnable(GL_TEXTURE_GEN_T);

  // Position The Text
  glTranslatef(1.1f * float(cos(rot / 16.0f)), 0.8f * float(sin(rot / 20.0f)),
               -3.0f);

  glRotatef(xRot, 1.0f, 0.0f, 0.0f);
  glRotatef(yRot, 0.0f, 1.0f, 0.0f);
  glRotatef(zRot, 0.0f, 0.0f, 1.0f);

  glRotatef(rot, 1.0f, 0.0f, 0.0f);        // Rotate On The X Axis
  glRotatef(rot * 1.2f, 0.0f, 1.0f, 0.0f); // Rotate On The Y Axis
  glRotatef(rot * 1.4f, 0.0f, 0.0f, 1.0f); // Rotate On The Z Axis

  glTranslatef(-0.35f, -0.35f, 0.1f); // Center On X, Y, Z Axis

  glPrint("N"); // Draw A Skull And Crossbones Symbol
  rot += 0.1f;  // Increase The Rotation Variable

  glDisable(GL_TEXTURE_GEN_S);
  glDisable(GL_TEXTURE_GEN_T);
}

} // namespace metarender::scenes::nehe
