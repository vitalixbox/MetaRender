#pragma once

#include <metarender/scene/IScene.hpp>

#include <array>
#include <glad/glad.h>

namespace metarender::scenes::nehe {

class Lesson13 : public IScene {
public:
	static constexpr metarender::SceneMetadata metadata() noexcept {
		return {
			.name = "Lesson13",
			.description = "Bitmap Fonts",
			.flags = SceneFlag_ShowInMenu
		};
	}

	void onEnter() override;
	void onUpdate(float deltaTime) override;
	void onRender() override;
	void onRenderUI() override;

private:
	GLuint m_texture = 0;

	GLuint  base;                           // Base Display List For The Font Set
	GLfloat cnt1;                           // 1st Counter Used To Move Text & For Coloring
	GLfloat cnt2;                           // 2nd Counter Used To Move Text & For Coloring

	float xRot = 0.0f;
	float yRot = 0.0f;
	float zRot = 0.0f;

	void BuildFont();
};

}