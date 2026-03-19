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
#include <glad/glad.h>
#include <imgui.h>

namespace metarender::scenes::nehe {

void Lesson13::onEnter() {
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
        -48,                            // Height Of Font ( NEW )
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

void Lesson13::KillFont() {
    glDeleteLists(base, 96);
}

void Lesson13::glPrint(const char *fmt, ...) {
    char        text[256];  // Holds Our String
    va_list     ap;         // Pointer To List Of Arguments

    if (fmt == nullptr) {
        return;
    }

    va_start(ap, fmt);                          // Parses The String For Variables
    vsprintf_s(text, sizeof(text), fmt, ap);    // And Converts Symbols To Actual Numbers
    va_end(ap);                                 // Results Are Stored In Text

    glPushAttrib(GL_LIST_BIT);              // Pushes The Display List Bits     ( NEW )
    glListBase(base - 32);                  // Sets The Base Character to 32    ( NEW )

    glCallLists(strlen(text), GL_UNSIGNED_BYTE, text);  // Draws The Display List Text  ( NEW )
    glPopAttrib();                                      // Pops The Display List Bits   ( NEW )
}

void Lesson13::onRender() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    m_renderer->perspective(45.0f, m_engine->getWindow().getAspectRatio(), 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glTranslatef(0.0f,0.0f,-1.0f);              // Move One Unit Into The Screen

	// Pulsing Colors Based On Text Position
	glColor3f(1.0f*float(cos(cnt1)),1.0f*float(sin(cnt2)),1.0f-0.5f*float(cos(cnt1+cnt2)));
	// Position The Text On The Screen
	glRasterPos2f(-0.45f+0.05f*float(cos(cnt1)), 0.35f*float(sin(cnt2)));
	glPrint("Active OpenGL Text With NeHe - %7.2f", cnt1);  // Print GL Text To The Screen
	cnt1+=0.051f;                       // Increase The First Counter
    cnt2+=0.005f;                       // Increase The Second Counter
}

}
