#pragma once

#include <string>

namespace metarender {

class Engine;
class IRenderer;
class AssetManager;

using SceneFlags = uint32_t;
inline constexpr SceneFlags SceneFlag_None = 0;
inline constexpr SceneFlags SceneFlag_ShowInMenu = 1u << 0;

struct SceneMetadata {
	std::string_view name;
	std::string_view description;
	SceneFlags flags = SceneFlag_None;
};

class IScene {
public:
	virtual ~IScene() = default;

	virtual void onEnter() {}
	virtual void onExit() {}
	virtual void onUpdate(float deltaTime) {}
	virtual void onRender() = 0;
	virtual void onRenderUI() {}

protected:
	Engine* m_engine = nullptr;
	IRenderer* m_renderer = nullptr;
	AssetManager* m_assetManager = nullptr;

	friend class SceneManager;
};

}