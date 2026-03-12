#pragma once

#include <metarender/scene/IScene.hpp>

namespace metarender::scenes::nehe {

class Lesson02 : public IScene {
public:
	static constexpr metarender::SceneMetadata metadata() noexcept {
		return {
			.name = "Lesson02",
			.description = "Your First Polygon",
			.flags = SceneFlag_ShowInMenu
		};
	}

	void onRender() override;
	void onEnter() override;
	void onRenderUI() override;

private:
	float m_triX = 0.0f;
	float m_triY = 0.0f;
	float m_triZ = 0.0f;
	float m_quadX = 0.0f;
	float m_quadY = 0.0f;
	float m_quadZ = 0.0f;
};

}
