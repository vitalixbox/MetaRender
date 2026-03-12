#include "SceneManager.hpp"
#include "IScene.hpp"

#include <metarender/log/Log.hpp>
#include <metarender/renderer/IRenderer.hpp>
#include <metarender/core/Engine.hpp>

namespace metarender {

SceneManager::SceneManager(Engine& engine)
	: m_engine(engine) {
}

SceneManager::~SceneManager() {
	if (m_currentScene) {
		m_currentScene->onExit();
	}
}

void SceneManager::loadScene(std::string name) {
	auto it = m_factories.find(name);
	if (it == m_factories.end()) {
		LOG_ERROR("Scene '{}' not found", name);
		return;
	}

	if (m_currentScene) {
		LOG_INFO("Exiting scene: {}", m_currentSceneName);
		m_currentScene->onExit();
	}

	LOG_INFO("Loading scene: {}", name);
	m_currentScene = it->second();
	m_currentScene->m_engine = &m_engine;
	m_currentScene->m_renderer = &m_engine.getRenderer();
	m_currentSceneName = name;

	m_engine.getRenderer().initialize(m_engine.getWindow());
	m_currentScene->onEnter();
}

void SceneManager::reloadCurrentScene() {
	if (!m_currentSceneName.empty()) {
		loadScene(m_currentSceneName);
	}
}

}