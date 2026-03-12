#pragma once

#include <metarender/scene/IScene.hpp>

#include <array>
#include <glad/glad.h>

namespace metarender::scenes::nehe {

// Flag
class Lesson11 : public IScene {
public:
	static constexpr metarender::SceneMetadata metadata() noexcept {
		return {
			.name = "Lesson11",
			.description = "Flag Effect (Waving Texture)",
			.flags = SceneFlag_ShowInMenu
		};
	}

	void onEnter() override;
	void onUpdate(float deltaTime) override;
	void onRender() override;
	void onRenderUI() override;

private:
	GLuint m_texture = 0;
	GLfloat points[45][45][3];
	int wiggle_count = 0;
	GLfloat hold = 0.0f;

	float m_xRotSpeed = 10.0f;
	float m_yRotSpeed = 30.0f;
	float m_zRotSpeed = -50.0f;
	float m_xRot = 0.0f;
	float m_yRot = 0.0f;
	float m_zRot = 0.0f;
};

}