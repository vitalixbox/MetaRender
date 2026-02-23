#pragma once

#include <string>

namespace metarender {

class Engine;
class IRenderer;
class AssetManager;

class IScene {
public:
	virtual ~IScene() = default;

	virtual void onEnter() {}
	virtual void onExit() {}
	virtual void onUpdate(float deltaTime) {}
	virtual void onRender() = 0;
	virtual void onRenderUI() {}

	[[nodiscard]] virtual std::string getName() const = 0;

protected:
	Engine* m_engine = nullptr;
	IRenderer* m_renderer = nullptr;
	AssetManager* m_assetManager = nullptr;

	friend class SceneManager;
};

}