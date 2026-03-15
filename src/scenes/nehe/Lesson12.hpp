#pragma once

#include <metarender/scene/IScene.hpp>

#include <array>
#include <glad/glad.h>

namespace metarender::scenes::nehe {

class Lesson12 : public IScene {
public:
	static constexpr metarender::SceneMetadata metadata() noexcept {
		return {
			.name = "Lesson12",
			.description = "Display Lists",
			.flags = SceneFlag_ShowInMenu
		};
	}

	void onEnter() override;
	void onUpdate(float deltaTime) override;
	void onRender() override;
	void onRenderUI() override;

private:
	GLuint m_texture = 0;
	GLuint box;
	GLuint top;
	GLuint xloop;
	GLuint yloop;

	GLfloat boxcol[5][3] = {
		// Bright:  Red, Orange, Yellow, Green, Blue
		{1.0f,0.0f,0.0f},{1.0f,0.5f,0.0f},{1.0f,1.0f,0.0f},{0.0f,1.0f,0.0f},{0.0f,1.0f,1.0f}
	};

	GLfloat topcol[5][3] = {
		// Dark:  Red, Orange, Yellow, Green, Blue
		{.5f,0.0f,0.0f},{0.5f,0.25f,0.0f},{0.5f,0.5f,0.0f},{0.0f,0.5f,0.0f},{0.0f,0.5f,0.5f}
	};

	float xCubeRot = 0.0f;
	float yCubeRot = 0.0f;
	float xRot = 0.0f;
	float yRot = 0.0f;
	float zRot = 0.0f;

	void BuildLists();
};

}