#pragma once

#include <metarender/scene/IScene.hpp>

namespace metarender::scenes::nehe {

// Simple triangles
class Lesson02 : public IScene {
public:
	void onRender() override;
	void onEnter() override;
	void onRenderUI() override;
	[[nodiscard]] std::string getName() const override { return "Lesson02"; }

private:
	float m_triX = 0.0f;
	float m_triY = 0.0f;
	float m_triZ = 0.0f;
	float m_quadX = 0.0f;
	float m_quadY = 0.0f;
	float m_quadZ = 0.0f;
};

}
