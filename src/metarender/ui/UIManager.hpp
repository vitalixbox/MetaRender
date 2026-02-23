#pragma once

namespace metarender {

class Window;
class IRenderer;
class Engine;

class UIManager {
public:
    UIManager(Window& window, IRenderer& renderer);
    ~UIManager();

    void beginFrame();
    void endFrame();

    void renderEngineUI(Engine& engine);
	void beforeRenderSceneUI();
	void afterRenderSceneUI();

    void setVisible(bool visible) { m_visible = visible; }
    [[nodiscard]] bool isVisible() const { return m_visible; }
    [[nodiscard]] bool isSceneWindowVisible() const { return m_sceneWindowVisible; }

private:
    Window& m_window;
    IRenderer& m_renderer;
    bool m_visible = true;
    bool m_statusWindowVisible = true;
    bool m_sceneWindowVisible = true;

	int m_statusWindowHeight = 100;
	int m_sceneUIWidth = 300;
};

}