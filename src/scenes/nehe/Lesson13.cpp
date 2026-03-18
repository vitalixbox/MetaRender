#include "Lesson13.hpp"
#include "Lesson13.hpp"

#include <metarender/log/Log.hpp>
#include <metarender/renderer/IRenderer.hpp>
#include <metarender/core/Engine.hpp>
#include <metarender/core/AssetManager.hpp>
#include <metarender/input/InputManager.hpp>
#include <metarender/platform/Window.hpp>

#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>
#include <Windows.h>
#include <cstdio>
#include <glad/glad.h>
#include <imgui.h>

namespace metarender::scenes::nehe {

void Lesson13::onEnter() {
	m_texture = m_assetManager->loadTexture("assets/nehe/Cube.bmp");

	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);

	BuildFont();
}

void Lesson13::onUpdate(float deltaTime) {
}

void Lesson13::onRenderUI() {
    ImGui::Text("Rotate Scene");
    ImGui::SliderFloat("X", &xRot, -360, 360);
    ImGui::SliderFloat("Y", &yRot, -360, 360);
    ImGui::SliderFloat("Z", &zRot, -360, 360);
}

void Lesson13::BuildFont() {
    HFONT font;
    HFONT oldFont;

    GLFWwindow* window = m_engine->getWindow().getNativeHandle();
    HWND hwnd = glfwGetWin32Window(window);
    HDC hDC = GetDC(hwnd);

    base = glGenLists(96);  // Storage For 96 Characters ( NEW )
    font = CreateFont(
        -24,                            // Height Of Font ( NEW )
        0,                              // Width Of Font
        0,                              // Angle Of Escapement
        0,                              // Orientation Angle
        FW_BOLD,                        // Font Weight
        FALSE,                          // Italic
        FALSE,                          // Underline
        FALSE,                          // Strikeout
        ANSI_CHARSET,                   // Character Set Identifier
        OUT_TT_PRECIS,                  // Output Precision
        CLIP_DEFAULT_PRECIS,            // Clipping Precision
        ANTIALIASED_QUALITY,            // Output Quality
        FF_DONTCARE | DEFAULT_PITCH,    // Family And Pitch
        "Courier New"
    );

    oldFont = (HFONT)SelectObject(hDC, font);   // Selects The Font We Want
    wglUseFontBitmaps(hDC, 32, 96, base);       // Builds 96 Characters Starting At Character 32
    SelectObject(hDC, oldFont);                 // Selects The Font We Want
    DeleteObject(font);                         // Delete The Font
}

void Lesson13::onRender() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    m_renderer->perspective(45.0f, m_engine->getWindow().getAspectRatio(), 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glBindTexture(GL_TEXTURE_2D, m_texture);
}

}