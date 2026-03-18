#include <metarender/log/Log.hpp>
#include <metarender/core/Engine.hpp>
#include <metarender/scene/SceneManager.hpp>
#include <scenes/Sandbox.hpp>
#include <scenes/nehe/Lesson02.hpp>
#include <scenes/nehe/Lesson03.hpp>
#include <scenes/nehe/Lesson04.hpp>
#include <scenes/nehe/Lesson05.hpp>
#include <scenes/nehe/Lesson06.hpp>
#include <scenes/nehe/Lesson07.hpp>
#include <scenes/nehe/Lesson08.hpp>
#include <scenes/nehe/Lesson09.hpp>
#include <scenes/nehe/Lesson10.hpp>
#include <scenes/nehe/Lesson11.hpp>
#include <scenes/nehe/Lesson12.hpp>
#include <scenes/nehe/Lesson13.hpp>

int main(int arc, char* argv[]) {
	try {
		metarender::Log::init();

		metarender::Engine::CreateInfo engineInfo;
		engineInfo.configPath = "config/config.json";
		metarender::Engine engine(engineInfo);

		auto& scenes = engine.getSceneManager();
		scenes.registerScene<metarender::scenes::Sandbox>();
		scenes.registerScene<metarender::scenes::nehe::Lesson02>();
		scenes.registerScene<metarender::scenes::nehe::Lesson03>();
		scenes.registerScene<metarender::scenes::nehe::Lesson04>();
		scenes.registerScene<metarender::scenes::nehe::Lesson05>();
		scenes.registerScene<metarender::scenes::nehe::Lesson06>();
		scenes.registerScene<metarender::scenes::nehe::Lesson07>();
		scenes.registerScene<metarender::scenes::nehe::Lesson08>();
		scenes.registerScene<metarender::scenes::nehe::Lesson09>();
		scenes.registerScene<metarender::scenes::nehe::Lesson10>();
		scenes.registerScene<metarender::scenes::nehe::Lesson11>();
		scenes.registerScene<metarender::scenes::nehe::Lesson12>();
		scenes.registerScene<metarender::scenes::nehe::Lesson13>();
		scenes.loadScene<metarender::scenes::nehe::Lesson13>();

		engine.run();

	} catch (std::exception &e) {
		LOG_ERROR("Fatal errpr: {}", e.what());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
