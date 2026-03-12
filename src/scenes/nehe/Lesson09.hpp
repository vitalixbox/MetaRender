#pragma once

#include <metarender/scene/IScene.hpp>

#include <array>
#include <glad/glad.h>

namespace metarender::scenes::nehe {

typedef struct {	// Create A Structure For Star
	int r, g, b;	// Stars Color
	GLfloat dist;	// Stars Distance From Center
	GLfloat angle;	// Stars Current Angle
} stars;			// Structures Name Is Stars

const int NUM_STARS = 50;

class Lesson09 : public IScene {
public:
	static constexpr metarender::SceneMetadata metadata() noexcept {
		return {
			.name = "Lesson09",
			.description = "Moving Bitmaps In 3D Space",
			.flags = SceneFlag_ShowInMenu
		};
	}

	void onEnter() override;
	void onUpdate(float deltaTime) override;
	void onRender() override;
	void onRenderUI() override;

private:
	stars m_stars[NUM_STARS];
	GLuint m_texture = 0;

	GLfloat zoom = -15.0f;
	GLfloat tilt = 90.0f;
	GLfloat spin = 0;
	float spinSpeed = 0.01f;
	float distSpeed = 0.02f;
	bool twinkle = false;
};

}