#include "Engine.hpp"

#include <metarender/log/Log.hpp>
#include <metarender/config/Config.hpp>
#include <metarender/core/ServiceLocator.hpp>
#include <metarender/event/EventBus.hpp>
#include <metarender/platform/Window.hpp>
#include <metarender/scene/IScene.hpp>
#include <metarender/scene/SceneManager.hpp>
#include <metarender/renderer/GLRenderer.hpp>
#include <metarender/ui/UIManager.hpp>
#include <metarender/event/WindowEvents.hpp>
#include <metarender/core/AssetManager.hpp>
#include <metarender/input/InputManager.hpp>
#include <metarender/core/Time.hpp>

namespace metarender {

Engine::Engine(const CreateInfo& info) {
	initialize(info);
}

Engine::~Engine() {
	shutdown();
}

void Engine::initialize(const CreateInfo& info) {
	LOG_INFO("Initializing MetaRender Engine...");

	m_config = std::make_unique<Config>(info.configPath);
	m_eventBus = std::make_unique<EventBus>();
	ServiceLocator::provide<EventBus>(m_eventBus.get());

	Window::CreateInfo windowInfo;
	windowInfo.width = m_config->getInt("window.width", 1280);
	windowInfo.height = m_config->getInt("window.height", 720);
	windowInfo.title = m_config->getString("window.title", "MetaRender Graphics Engine");
	windowInfo.vsync = m_config->getBool("window.vsync", true);
	m_window = std::make_unique<Window>(windowInfo);

	m_inputManager = std::make_unique<InputManager>(*m_window);

	m_sceneManager = std::make_unique<SceneManager>(*this);

	m_renderer = std::make_unique<GLRenderer>();
	m_renderer->initialize(*m_window);
	m_eventBus->subscribe<WindowResizeEvent>([this](WindowResizeEvent& event) {
		m_renderer->resize();
	});

	m_ui = std::make_unique<UIManager>(*m_window, *m_renderer);

	m_time = std::make_unique<Time>();

	m_assetManager = std::make_unique<AssetManager>();

	LOG_INFO("Engine initialized successfully");
}

SceneManager& Engine::getSceneManager() {
	return *m_sceneManager;
}

Window& Engine::getWindow() {
	return *m_window;
}

IRenderer& Engine::getRenderer() {
	return *m_renderer;
}

AssetManager& Engine::getAssetManager() {
	return *m_assetManager;
}

UIManager& Engine::getUIManager() {
	return *m_ui;
}

InputManager& Engine::getInputManager() {
	return *m_inputManager;
}

void Engine::run() {
	m_running = true;
	mainLoop();
}

void Engine::requestShutdown() {
	m_running = false;
}

void Engine::mainLoop() {
	while (m_running && !m_window->shouldClose()) {
		m_time->update();
		const float deltaTime = m_time->getDeltaTime();

		m_window->pollEvents();
		m_inputManager->update();

		if (auto* scene = m_sceneManager->getCurrentScene()) {
			scene->onUpdate(deltaTime);
			scene->onRender();
		}

		m_ui->beginFrame();
		m_ui->renderEngineUI(*this);
		if (auto* scene = m_sceneManager->getCurrentScene()) {
			if (m_ui->isSceneWindowVisible()) {
				m_ui->beforeRenderSceneUI();
				scene->onRenderUI();
				m_ui->afterRenderSceneUI();
			}
		}
		m_ui->endFrame();

		m_window->swapBuffers();
	}
}

void Engine::shutdown() {
	LOG_INFO("Shutting down engine...");

	m_assetManager.reset();
	m_sceneManager.reset();
	m_ui.reset();
	m_renderer.reset();
	m_window.reset();
	m_eventBus.reset();
	m_config.reset();

	LOG_INFO("Engine shutdown complete");
}

}
