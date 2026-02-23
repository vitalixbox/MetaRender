#include "UIManager.hpp"

#include <metarender/platform/Window.hpp>
#include <metarender/renderer/IRenderer.hpp>
#include <metarender/core/Engine.hpp>
#include <metarender/scene/SceneManager.hpp>

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl2.h>
#include <GLFW/glfw3.h>

namespace metarender {

UIManager::UIManager(Window& window, IRenderer& renderer)
	: m_window(window)
	, m_renderer(renderer) {
    float main_scale = ImGui_ImplGlfw_GetContentScaleForMonitor(glfwGetPrimaryMonitor());

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);
    style.FontScaleDpi = main_scale;

    ImGui_ImplGlfw_InitForOpenGL(window.getNativeHandle(), true);
    ImGui_ImplOpenGL2_Init();
}

UIManager::~UIManager() {
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void UIManager::beginFrame() {
    ImGui_ImplOpenGL2_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void UIManager::endFrame() {
    ImGui::Render();
    ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
}

void UIManager::renderEngineUI(Engine& engine) {
    if (!m_visible) return;

    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Quit", "Alt+F4")) {
                engine.requestShutdown();
            }
            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Scenes")) {
			auto& sceneManager = engine.getSceneManager();
			const auto& sceneNames = sceneManager.getSceneNames();
			const auto& currentName = sceneManager.getCurrentSceneName();

			for (const auto& name : sceneNames) {
				if (ImGui::MenuItem(name.c_str(), "")) {
					sceneManager.loadScene(name);
				}
			}

            ImGui::EndMenu();
        }

        if (ImGui::BeginMenu("Window")) {
            if (ImGui::MenuItem("Status", "")) {
                m_statusWindowVisible = !m_statusWindowVisible;
            }
            if (ImGui::MenuItem("Scene UI", "")) {
                m_sceneWindowVisible = !m_sceneWindowVisible;
            }

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    if (m_statusWindowVisible) {
        ImGuiIO& io = ImGui::GetIO();

        ImGui::SetNextWindowPos(ImVec2(0, io.DisplaySize.y - m_statusWindowHeight));
        ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x, m_statusWindowHeight), ImGuiCond_Always);

        if (ImGui::Begin("Stats", nullptr,
            ImGuiWindowFlags_NoCollapse |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoDecoration
        )) {
            ImGui::Text("Scene: %s", engine.getSceneManager().getCurrentSceneName().c_str());
            // Get Time service somehow (we'd need to pass it or use ServiceLocator)
            ImGui::Text("Window: %dx%d", m_window.getWidth(), m_window.getHeight());
        }
        ImGui::End();
    }
}

void UIManager::beforeRenderSceneUI() {
	ImGuiIO& io = ImGui::GetIO();

    float menuHeight = ImGui::GetFrameHeight();
	ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x - m_sceneUIWidth, menuHeight));
	ImGui::SetNextWindowSize(ImVec2(m_sceneUIWidth, io.DisplaySize.y - m_statusWindowHeight - menuHeight), ImGuiCond_Always);
    ImGui::Begin("Scene UI", nullptr,
        ImGuiWindowFlags_NoMove);
}

void UIManager::afterRenderSceneUI() {
    ImGui::End();
}

}