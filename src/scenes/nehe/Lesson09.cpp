#include "Lesson09.hpp"

#include <metarender/log/Log.hpp>
#include <metarender/renderer/IRenderer.hpp>
#include <metarender/core/Engine.hpp>
#include <metarender/core/AssetManager.hpp>
#include <metarender/platform/Window.hpp>

#include <glad/glad.h>
#include <imgui.h>

namespace metarender::scenes::nehe {

void Lesson09::onEnter() {
	m_texture = m_assetManager->loadTexture("assets/nehe/star.bmp");

	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glEnable(GL_BLEND);

    for (GLuint loop = 0; loop < NUM_STARS; loop++) {
        m_stars[loop].angle = 0.0f;
        m_stars[loop].dist = (float(loop) / NUM_STARS) * 5.0f;
        m_stars[loop].r = rand() % 256;
        m_stars[loop].g = rand() % 256;
        m_stars[loop].b = rand() % 256;
    }

	zoom = -15.0f;
	tilt = 90.0f;
	spin = 0;
    twinkle = false;
}

void Lesson09::onUpdate(float deltaTime) {
}

void Lesson09::onRenderUI() {
    ImGui::SeparatorText("Starfield");

    ImGui::Checkbox("Twinkle", &twinkle);

    ImGui::SetNextItemWidth(140.0f);
    ImGui::DragFloat("Spin speed", &spinSpeed, 0.001f, 0.0f, 1.0f, "%.4f");

    ImGui::SetNextItemWidth(140.0f);
    ImGui::DragFloat("Distance speed", &distSpeed, 0.001f, 0.0f, 1.0f, "%.4f");

    if (ImGui::Button("Reset")) {
        spinSpeed = 0.01f;
        distSpeed = 0.02f;
        twinkle = false;
    }
}

void Lesson09::onRender() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    m_renderer->perspective(45.0f, m_engine->getWindow().getAspectRatio(), 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBindTexture(GL_TEXTURE_2D, m_texture);

    for (GLuint loop = 0; loop < NUM_STARS; loop++) {   // Loop Through All The Stars
        glLoadIdentity();                               // Reset The View Before We Draw Each Star
        glTranslatef(0.0f, 0.0f, zoom);                 // Zoom Into The Screen (Using The Value In 'zoom')
        glRotatef(tilt, 1.0f, 0.0f, 0.0f);              // Tilt The View (Using The Value In 'tilt')

        glRotatef(m_stars[loop].angle, 0.0f, 1.0f, 0.0f);   // Rotate To The Current Stars Angle
        glTranslatef(m_stars[loop].dist, 0.0f, 0.0f);       // Move Forward On The X Plane

        glRotatef(-m_stars[loop].angle, 0.0f, 1.0f, 0.0f);  // Cancel The Current Stars Angle
        glRotatef(-tilt, 1.0f, 0.0f, 0.0f);                 // Cancel The Screen Tilt

        if (twinkle) {  // Twinkling Stars Enabled
            // Assign A Color Using Bytes
            glColor4ub(m_stars[(NUM_STARS - loop) - 1].r, m_stars[(NUM_STARS - loop) - 1].g, m_stars[(NUM_STARS - loop) - 1].b, 255);
            glBegin(GL_QUADS);  // Begin Drawing The Textured Quad
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0.0f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0.0f);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
            glEnd();            // Done Drawing The Textured Quad
        }

        glRotatef(spin, 0.0f, 0.0f, 1.0f);  // Rotate The Star On The Z Axis
        // Assign A Color Using Bytes
        glColor4ub(m_stars[loop].r, m_stars[loop].g, m_stars[loop].b, 255);
        glBegin(GL_QUADS);  // Begin Drawing The Textured Quad
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 0.0f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(1.0f, -1.0f, 0.0f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(1.0f, 1.0f, 0.0f);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
        glEnd();

        spin += spinSpeed;                                  // Used To Spin The Stars
        m_stars[loop].angle += float(loop) / NUM_STARS;     // Changes The Angle Of A Star
        m_stars[loop].dist -= distSpeed;                    // Changes The Distance Of A Star

        if (m_stars[loop].dist < 0.0f) {                    // Is The Star In The Middle Yet
            m_stars[loop].dist += 5.0f;                     // Move The Star 5 Units From The Center
            m_stars[loop].r = rand() % 256;                 // Give It A New Red Value
            m_stars[loop].g = rand() % 256;                 // Give It A New Green Value
            m_stars[loop].b = rand() % 256;                 // Give It A New Blue Value
        }
    }
}

}