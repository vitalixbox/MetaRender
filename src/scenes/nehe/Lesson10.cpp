#include "Lesson10.hpp"

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

void Lesson10::onEnter() {
	TextureData data = m_assetManager->loadTextureData("assets/nehe/mud.bmp");

    glEnable(GL_TEXTURE_2D);
	glGenTextures(3, m_textures.data());

	// --- Texture 0: Nearest ---
	glBindTexture(GL_TEXTURE_2D, m_textures.at(0));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, data.width, data.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data);

	// --- Texture 1: Linear ---
	glBindTexture(GL_TEXTURE_2D, m_textures.at(1));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, data.width, data.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data);

	// --- Texture 2: Mipmapped ---
	glBindTexture(GL_TEXTURE_2D, m_textures.at(2));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, data.width, data.height, 0, GL_RGB, GL_UNSIGNED_BYTE, data.data);
    glGenerateMipmap(GL_TEXTURE_2D);

	setupWorld();

	walkbias = 0;
	walkbiasangle = 0;
	lookupdown = 0.0f;
	heading = 0.0f;
	xpos = 0.0f;
	zpos = 0.0f;
	yrot = 0.0f;
}

void Lesson10::setupWorld() {
	float x, y, z, u, v;
	int numtriangles;
	FILE* filein;
	char oneline[255];
	filein = fopen("assets/nehe/world.txt", "rt");

	readstr(filein, oneline);
	sscanf(oneline, "NUMPOLLIES %d\n", &numtriangles);

	sector1.triangle = new TRIANGLE[numtriangles];
	sector1.numtriangles = numtriangles;
	for (int loop = 0; loop < numtriangles; loop++) {
		for (int vert = 0; vert < 3; vert++) {
			readstr(filein, oneline);
			sscanf(oneline, "%f %f %f %f %f", &x, &y, &z, &u, &v);
			sector1.triangle[loop].vertex[vert].x = x;
			sector1.triangle[loop].vertex[vert].y = y;
			sector1.triangle[loop].vertex[vert].z = z;
			sector1.triangle[loop].vertex[vert].u = u;
			sector1.triangle[loop].vertex[vert].v = v;
		}
	}
	fclose(filein);

	return;
}

void Lesson10::onUpdate(float deltaTime) {
	if (m_engine->getInputManager().isKeyDown(Key::Up) || m_engine->getInputManager().isKeyDown(Key::W)) {
		xpos -= (float)sin(heading * piover180) * 0.05f;
		zpos -= (float)cos(heading * piover180) * 0.05f;
		if (walkbiasangle >= 359.0f) {
			walkbiasangle = 0.0f;
		}
		else {
			walkbiasangle += 10;
		}
		walkbias = (float)sin(walkbiasangle * piover180) / 20.0f;
	}

	if (m_engine->getInputManager().isKeyDown(Key::Down) || m_engine->getInputManager().isKeyDown(Key::S)) {
		xpos += (float)sin(heading * piover180) * 0.05f;
		zpos += (float)cos(heading * piover180) * 0.05f;
		if (walkbiasangle <= 1.0f) {
			walkbiasangle = 359.0f;
		}
		else {
			walkbiasangle -= 10;
		}
		walkbias = (float)sin(walkbiasangle * piover180) / 20.0f;
	}

	if (m_engine->getInputManager().isKeyDown(Key::Left) || m_engine->getInputManager().isKeyDown(Key::A)) {
		heading += 1.0f;
		yrot = heading;
	}

	if (m_engine->getInputManager().isKeyDown(Key::Right) || m_engine->getInputManager().isKeyDown(Key::D)) {
		heading -= 1.0f;
		yrot = heading;
	}

	if (m_engine->getInputManager().isKeyDown(Key::PageUp)) {
		lookupdown -= 1.0f;
	}

	if (m_engine->getInputManager().isKeyDown(Key::PageDown)) {
		lookupdown += 1.0f;
	}
}

void Lesson10::onRenderUI() {
}

void Lesson10::onRender() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    m_renderer->perspective(45.0f, m_engine->getWindow().getAspectRatio(), 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	GLfloat x_m, y_m, z_m, u_m, v_m;
	GLfloat xtrans = -xpos;
	GLfloat ztrans = -zpos;
	GLfloat ytrans = -walkbias - 0.25f;
	GLfloat sceneroty = 360.0f - yrot;

	int numtriangles = sector1.numtriangles;
    glBindTexture(GL_TEXTURE_2D, m_textures.at(m_currentFilter));

	glRotatef(lookupdown, 1.0f, 0, 0);
	glRotatef(sceneroty, 0, 1.0f, 0);
	glTranslatef(xtrans, ytrans, ztrans);

    for (int loop_m = 0; loop_m < numtriangles; loop_m++) { // Loop Through All The Triangles
        glBegin(GL_TRIANGLES);								// Start Drawing Triangles
        glNormal3f(0.0f, 0.0f, 1.0f);						// Normal Pointing Forward
        x_m = sector1.triangle[loop_m].vertex[0].x;			// X Vertex Of 1st Point
        y_m = sector1.triangle[loop_m].vertex[0].y;			// Y Vertex Of 1st Point
        z_m = sector1.triangle[loop_m].vertex[0].z;			// Z Vertex Of 1st Point
        u_m = sector1.triangle[loop_m].vertex[0].u;			// U Texture Coord Of 1st Point
        v_m = sector1.triangle[loop_m].vertex[0].v;			// V Texture Coord Of 1st Point
        glTexCoord2f(u_m, v_m); glVertex3f(x_m, y_m, z_m);	// Set The TexCoord And Vertice

        x_m = sector1.triangle[loop_m].vertex[1].x;			// X Vertex Of 2nd Point
        y_m = sector1.triangle[loop_m].vertex[1].y;			// Y Vertex Of 2nd Point
        z_m = sector1.triangle[loop_m].vertex[1].z;			// Z Vertex Of 2nd Point
        u_m = sector1.triangle[loop_m].vertex[1].u;			// U Texture Coord Of 2nd Point
        v_m = sector1.triangle[loop_m].vertex[1].v;			// V Texture Coord Of 2nd Point
        glTexCoord2f(u_m, v_m); glVertex3f(x_m, y_m, z_m);	// Set The TexCoord And Vertice

        x_m = sector1.triangle[loop_m].vertex[2].x;			// X Vertex Of 3rd Point
        y_m = sector1.triangle[loop_m].vertex[2].y;			// Y Vertex Of 3rd Point
        z_m = sector1.triangle[loop_m].vertex[2].z;			// Z Vertex Of 3rd Point
        u_m = sector1.triangle[loop_m].vertex[2].u;			// U Texture Coord Of 3rd Point
        v_m = sector1.triangle[loop_m].vertex[2].v;			// V Texture Coord Of 3rd Point
        glTexCoord2f(u_m, v_m); glVertex3f(x_m, y_m, z_m);	// Set The TexCoord And Vertice
        glEnd();											// Done Drawing Triangles
    }
}

}