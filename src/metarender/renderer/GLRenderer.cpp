#include "GLRenderer.hpp"

#include <metarender/platform/Window.hpp>
#include <metarender/log/Log.hpp>

#include <glad/glad.h>
#include <cmath>

namespace metarender {

GLRenderer::GLRenderer() = default;
GLRenderer::~GLRenderer() = default;

void GLRenderer::initialize(Window& window) {
	m_window = &window;
	resize();

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glClearDepth(1.0f);

    glShadeModel(GL_SMOOTH);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHTING);
	glDisable(GL_BLEND);
}

void GLRenderer::resize() {
    glViewport(0, 0, m_window->getWidth(), m_window->getHeight());
}

void GLRenderer::perspective(float fovY, float aspect, float nearZ, float farZ) {
	// Implement gluPerspective manually
	const float DEG2RAD = 3.14159265358979323846f / 180.0f;
	const float fH = std::tan(fovY * 0.5f * DEG2RAD) * nearZ;
	const float fW = fH * aspect;
	glFrustum(-fW, fW, -fH, fH, nearZ, farZ);
}

}