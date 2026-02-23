#pragma once

#include <string>
#include <functional>

struct GLFWwindow;

namespace metarender {

class Window {
public:
	struct CreateInfo {
		int width = 1280;
		int height = 720;
		std::string title = "MetaRender Graphics Engine";
		bool vsync = true;
		bool fullscreen = false;
		bool resizable = true;
	};

	explicit Window(const CreateInfo& info);
	~Window();

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	void pollEvents();
	void swapBuffers();

	[[nodiscard]] bool shouldClose() const;
	void setShouldClose(bool value);

	[[nodiscard]] int getWidth() const { return m_width; }
	[[nodiscard]] int getHeight() const { return m_height; }
	[[nodiscard]] float getAspectRatio() const;
	[[nodiscard]] GLFWwindow* getNativeHandle() const { return m_window; }
	void setVSync(bool enabled);
	[[nodiscard]] bool isVSync() const { return m_vsync; }

private:
	void initGLFW();
	void createWindow(const CreateInfo& info);
	void setupCallbacks();

	GLFWwindow* m_window = nullptr;
	int m_width = 0;
	int m_height = 0;
	bool m_vsync = true;
};

}