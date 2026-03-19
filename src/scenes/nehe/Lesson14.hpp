#pragma once

#include <metarender/scene/IScene.hpp>

#include <windows.h>
#include <glad/glad.h>

namespace metarender::scenes::nehe {

class Lesson14 : public IScene {
public:
	static constexpr metarender::SceneMetadata metadata() noexcept {
		return {
			.name = "Lesson14",
			.description = "Outline Fonts",
			.flags = SceneFlag_ShowInMenu
		};
	}

	void onEnter() override;
	void onUpdate(float deltaTime) override;
	void onRender() override;
	void onRenderUI() override;

private:
	GLuint  base;                           // Base Display List For The Font Set
	GLYPHMETRICSFLOAT gmf[256];

	float rot = 0.0f;
	float xRot = 0.0f;
	float yRot = 0.0f;
	float zRot = 0.0f;

	void BuildFont();
	void KillFont();
	void glPrint(const char *fmt, ...);
};

}
