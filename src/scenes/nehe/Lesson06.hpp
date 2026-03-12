#pragma once

#include <metarender/scene/IScene.hpp>

#include <glad/glad.h>

namespace metarender::scenes::nehe {

class Lesson06 : public IScene {
public:
	static constexpr metarender::SceneMetadata metadata() noexcept {
		return {
			.name = "Lesson06",
			.description = "Texture Mapping",
			.flags = SceneFlag_ShowInMenu
		};
	}

	void onEnter() override;
	void onUpdate(float deltaTime) override;
	void onRender() override;
	void onRenderUI() override;

private:
	GLuint m_texture = 0;
	float m_xRotSpeed = 10.0f;
	float m_yRotSpeed = 30.0f;
	float m_zRotSpeed = -50.0f;
	float m_xRot = 0.0f;
	float m_yRot = 0.0f;
	float m_zRot = 0.0f;
};

}