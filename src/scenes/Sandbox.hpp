#pragma once

#include <metarender/scene/IScene.hpp>
#include <metarender/renderer/IRenderer.hpp>

namespace metarender::scenes {

class Sandbox : public IScene {
public:
	void onEnter() override;
	void onRender() override;
	[[nodiscard]] std::string getName() const override { return "Sandbox"; }
};

}