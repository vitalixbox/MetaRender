#pragma once

#include <metarender/scene/IScene.hpp>

namespace metarender::scenes::nehe {

// Tor and Cube
class Lesson05 : public IScene {
public:
	void onEnter() override;
	void onUpdate(float deltaTime) override;
	void onRender() override;
	void onRenderUI() override;
	[[nodiscard]] std::string getName() const override { return "Lesson05"; }

private:
	float m_triangleRotation = 0.0f;
	float m_quadRotation = 0.0f;
	float m_rotationSpeed = 100.0f;
};

}