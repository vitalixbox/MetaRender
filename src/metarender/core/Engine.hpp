#pragma once

#include <string>
#include <memory>

namespace metarender {

class Config;
class EventBus;
class Window;
class SceneManager;
class IRenderer;
class UIManager;
class Time;
class AssetManager;
class InputManager;

class Engine {
public:
	struct CreateInfo {
		std::string configPath = "config/config.json";
	};

	explicit Engine(const CreateInfo& info);
	~Engine();

	Engine(const Engine&) = delete;
	Engine& operator=(const Engine&) = delete;

	[[nodiscard]] SceneManager& getSceneManager();
	[[nodiscard]] Window& getWindow();
	[[nodiscard]] IRenderer& getRenderer();
	[[nodiscard]] AssetManager& getAssetManager();
	[[nodiscard]] UIManager& getUIManager();
	[[nodiscard]] InputManager& getInputManager();

	void run();
	void requestShutdown();

private:
	void initialize(const CreateInfo& info);
	void shutdown();
	void mainLoop();

	std::unique_ptr<Config>			m_config;
	std::unique_ptr<EventBus>		m_eventBus;
	std::unique_ptr<Window>			m_window;
	std::unique_ptr<SceneManager>	m_sceneManager;
	std::unique_ptr<IRenderer>		m_renderer;
	std::unique_ptr<AssetManager>	m_assetManager;
	std::unique_ptr<InputManager>	m_inputManager;
	std::unique_ptr<UIManager>		m_ui;
	std::unique_ptr<Time>			m_time;

	bool m_running = false;
};

}
