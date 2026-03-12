#pragma once

#include <metarender/scene/IScene.hpp>

#include <array>
#include <glad/glad.h>

namespace metarender::scenes::nehe {

class Lesson08 : public IScene {
public:
	static constexpr metarender::SceneMetadata metadata() noexcept {
		return {
			.name = "Lesson08",
			.description = "Blending",
			.flags = SceneFlag_ShowInMenu
		};
	}

	void onEnter() override;
	void onUpdate(float deltaTime) override;
	void onRender() override;
	void onRenderUI() override;

private:
	std::array<GLuint, 3> m_textures{ 0, 0, 0 };
	int m_currentFilter = 0;
	std::array<GLfloat, 4> m_lightAmbient{ 0.5f, 0.5f, 0.5f, 1.0f };
	std::array<GLfloat, 4> m_lightDiffuse{ 1.0f, 1.0f, 1.0f, 1.0f };
	std::array<GLfloat, 4> m_lightPosition{ 0.0f, 0.0f, 2.0f, 1.0f };

	float m_xRotSpeed = 10.0f;
	float m_yRotSpeed = 30.0f;
	float m_zRotSpeed = -50.0f;
	float m_xRot = 0.0f;
	float m_yRot = 0.0f;
	float m_zRot = 0.0f;
	bool  m_enableBlending = true;
};

}