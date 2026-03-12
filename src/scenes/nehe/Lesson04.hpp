#pragma once

#include <metarender/scene/IScene.hpp>

namespace metarender::scenes::nehe {

class Lesson04 : public IScene {
public:
	static constexpr metarender::SceneMetadata metadata() noexcept {
		return {
			.name = "Lesson04",
			.description = "Rotation",
			.flags = SceneFlag_ShowInMenu
		};
	}

	void onEnter() override;
	void onUpdate(float deltaTime) override;
	void onRender() override;
	void onRenderUI() override;

private:
	float m_triangleRotation = 0.0f;
	float m_quadRotation = 0.0f;
	float m_rotationSpeed = 100.0f;
};

}