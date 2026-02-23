#pragma once

#include <functional>
#include <memory>
#include <unordered_map>
#include <vector>
#include <string>

namespace metarender {

class IScene;
class Engine;

class SceneManager {
public:
	using SceneFactory = std::function<std::unique_ptr<IScene>()>;

	explicit SceneManager(Engine& engine);
	~SceneManager();

	template<typename SceneType>
	void registerScene(const std::string name) {
		m_factories[name] = []() { return std::make_unique<SceneType>();  };
		m_sceneNames.push_back(name);
	}

	void loadScene(std::string name);
	void reloadCurrentScene();

	[[nodiscard]] IScene* getCurrentScene() const { return m_currentScene.get(); }
	[[nodiscard]] const std::string& getCurrentSceneName() const { return m_currentSceneName; }
	[[nodiscard]] const std::vector<std::string>& getSceneNames() const { return m_sceneNames; }

private:
	Engine& m_engine;
	std::unique_ptr<IScene> m_currentScene;
	std::string m_currentSceneName;
	std::unordered_map<std::string, SceneFactory> m_factories;
	std::vector<std::string> m_sceneNames;
};

}