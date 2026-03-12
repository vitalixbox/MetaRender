#pragma once

#include <metarender/scene/IScene.hpp>

#include <array>
#include <glad/glad.h>

namespace metarender::scenes::nehe {

typedef struct tagVERTEX {	// Build Our Vertex Structure
	float x, y, z;          // 3D Coordinates
	float u, v;             // Texture Coordinates
} VERTEX;

typedef struct tagTRIANGLE {	// Build Our Triangle Structure
	VERTEX vertex[3];			// Array Of Three Vertices
} TRIANGLE;

typedef struct tagSECTOR {	// Build Our Sector Structure
	int numtriangles;		// Number Of Triangles In Sector
	TRIANGLE* triangle;		// Pointer To Array Of Triangles
} SECTOR;

class Lesson10 : public IScene {
public:
	static constexpr metarender::SceneMetadata metadata() noexcept {
		return {
			.name = "Lesson10",
			.description = "Loading And Moving Through A 3D World",
			.flags = SceneFlag_ShowInMenu
		};
	}

	void onEnter() override;
	void onUpdate(float deltaTime) override;
	void onRender() override;
	void onRenderUI() override;
	void setupWorld();
	void readstr(FILE* f, char* string) {
		do {
			fgets(string, 255, f);
		} while ((string[0] == '/') || (string[0] == '\n'));
		return;
	}

private:
	std::array<GLuint, 3> m_textures{ 0, 0, 0 };
	int m_currentFilter = 0;
	SECTOR sector1;

	GLfloat	yrot = 0.0f;
	GLfloat walkbias = 0;
	GLfloat walkbiasangle = 0;
	GLfloat lookupdown = 0.0f;
	const float piover180 = 0.0174532925f;
	float heading = 0.0f;
	float xpos = 0.0f;
	float zpos = 0.0f;
};

}