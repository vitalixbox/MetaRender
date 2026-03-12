#pragma once

#include <metarender/scene/IScene.hpp>
#include <metarender/renderer/IRenderer.hpp>

namespace metarender::scenes {

class Sandbox : public IScene {
public:
	static constexpr metarender::SceneMetadata metadata() noexcept {
		return {
			.name = "Sandbox",
			.description = "Empty scene for experimenting",
			.flags = SceneFlag_ShowInMenu
		};
	}

	void onEnter() override;
	void onRender() override;
};

}