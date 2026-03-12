#pragma once

#include <metarender/scene/IScene.hpp>

#include <imgui.h>

namespace metarender::scenes::nehe {

class Lesson03 : public IScene {
public:
	static constexpr metarender::SceneMetadata metadata() noexcept {
		return {
			.name = "Lesson03",
			.description = "Adding Color",
			.flags = SceneFlag_ShowInMenu
		};
	}

	void onRender() override;
	void onEnter() override;
	void onRenderUI() override;

private:
	ImVec4 p1 = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	ImVec4 p2 = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
	ImVec4 p3 = ImVec4(0.0f, 0.0f, 1.0f, 1.0f);
	ImVec4 quad = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
};

}