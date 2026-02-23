#pragma once

#include <metarender/scene/IScene.hpp>

#include <imgui.h>

namespace metarender::scenes::nehe {

// Coloring
class Lesson03 : public IScene {
public:
	void onRender() override;
	void onEnter() override;
	void onRenderUI() override;
	[[nodiscard]] std::string getName() const override { return "Lesson03"; }

private:
	ImVec4 p1 = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
	ImVec4 p2 = ImVec4(0.0f, 1.0f, 0.0f, 1.0f);
	ImVec4 p3 = ImVec4(0.0f, 0.0f, 1.0f, 1.0f);
	ImVec4 quad = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
};

}