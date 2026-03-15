#include "Lesson12.hpp"

#include <metarender/log/Log.hpp>
#include <metarender/renderer/IRenderer.hpp>
#include <metarender/core/Engine.hpp>
#include <metarender/core/AssetManager.hpp>
#include <metarender/input/InputManager.hpp>
#include <metarender/platform/Window.hpp>

#include <cstdio>
#include <glad/glad.h>
#include <imgui.h>

namespace metarender::scenes::nehe {

void Lesson12::onEnter() {
	m_texture = m_assetManager->loadTexture("assets/nehe/Cube.bmp");

	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);

	BuildLists();
}

void Lesson12::onUpdate(float deltaTime) {
    xCubeRot += 20.0f * deltaTime;
    yCubeRot += 15.0f * deltaTime;

    if (xCubeRot > 360.0f) xCubeRot -= 360.0f;
    if (yCubeRot > 360.0f) yCubeRot -= 360.0f;
    if (xCubeRot < -360.0f) xCubeRot = 360.0f;
    if (yCubeRot < -360.0f) yCubeRot = 360.0f;
}

void Lesson12::onRenderUI() {
    ImGui::Text("Rotate Scene");
    ImGui::SliderFloat("X", &xRot, -360, 360);
    ImGui::SliderFloat("Y", &yRot, -360, 360);
    ImGui::SliderFloat("Z", &zRot, -360, 360);
}

void Lesson12::BuildLists() {
    box = glGenLists(2);

    glNewList(box, GL_COMPILE);
    glBegin(GL_QUADS);                          // Start Drawing Quads
    // Bottom Face
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, -1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom Right Of The Texture and Quad
    // Front Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);  // Top Left Of The Texture and Quad
    // Back Face
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
    // Right face
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(1.0f, -1.0f, 1.0f);  // Bottom Left Of The Texture and Quad
    // Left Face
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 1.0f);  // Top Right Of The Texture and Quad
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glEnd();                                // Done Drawing Quads
    glEndList(); // Done Building The box List

    top = box + 1;                                  // top List Value Is box List Value +1
    glNewList(top, GL_COMPILE);                          // New Compiled top Display List
    glBegin(GL_QUADS);                          // Start Drawing Quad
    // Top Face
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f);  // Top Left Of The Texture and Quad
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f);  // Bottom Left Of The Texture and Quad
    glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f);  // Bottom Right Of The Texture and Quad
    glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f);  // Top Right Of The Texture and Quad
    glEnd();
    glEndList();                                    // Done Building The top Display List
}

void Lesson12::onRender() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    m_renderer->perspective(45.0f, m_engine->getWindow().getAspectRatio(), 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glBindTexture(GL_TEXTURE_2D, m_texture);

    for (yloop = 1; yloop < 6; yloop++) {
        for (xloop = 0; xloop < yloop; xloop++) {
            glLoadIdentity();

            glTranslatef(0.0f, 0.0f, -20.0f);
			glRotatef(xRot, 1.0f, 0.0f, 0.0f);
			glRotatef(yRot, 0.0f, 1.0f, 0.0f);
			glRotatef(zRot, 0.0f, 0.0f, 1.0f);

            // Position The Cubes On The Screen
            glTranslatef(1.4f + (float(xloop) * 2.8f) - (float(yloop) * 1.4f), ((6.0f - float(yloop)) * 2.4f) - 7.0f, 0.0f);

            glRotatef(45.0f - (2.0f * yloop) + xCubeRot, 1.0f, 0.0f, 0.0f);      // Tilt The Cubes Up And Down
            glRotatef(45.0f + yCubeRot, 0.0f, 1.0f, 0.0f);               // Spin Cubes Left And Right

            glColor3fv(boxcol[yloop - 1]);  // Select A Box Color
            glCallList(box);                // Draw The Box
            glColor3fv(topcol[yloop - 1]);  // Select The Top Color
            glCallList(top);
        }
    }
}

}