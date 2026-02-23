#include "InputManager.hpp"

#include <metarender/platform/Window.hpp>
#include <metarender/log/Log.hpp>

#include <GLFW/glfw3.h>

namespace metarender {

static InputManager* s_instance = nullptr;

static constexpr Key kKeysToPoll[] = {
	Key::W, Key::A, Key::S, Key::D,
	Key::Space, Key::LeftShift,
	Key::Escape,
	Key::Left, Key::Right, Key::Up, Key::Down
};

InputManager::InputManager(Window& window)
	: m_window(window) {
	s_instance = this;
}

InputManager::~InputManager() {
	s_instance = nullptr;
}

void InputManager::update() {
	m_previousKeyState = m_currentKeyState;

	GLFWwindow* h = m_window.getNativeHandle();
	for (Key key : KeyUtil::AllKeys) {
		int code = static_cast<int>(key); // same as GLFW code (in your current design)
		if (code < 0) continue; // skips Key::Unknown = -1
		bool isPressed = glfwGetKey(h, code) == GLFW_PRESS;
		if (isPressed) {
			LOG_INFO("Key {} is pressed", KeyUtil::toString(key));
		}
		m_currentKeyState[code] = isPressed;
	}
}

// Keyboard queries
bool InputManager::isKeyDown(Key key) const {
	const auto index = static_cast<size_t>(key);
	return index < MAX_KEYS && m_currentKeyState[index];
}

bool InputManager::isKeyUp(Key key) const {
	return !isKeyDown(key);
}

bool InputManager::wasKeyPressed(Key key) const {
	const auto index = static_cast<size_t>(key);
	return index < MAX_KEYS && m_currentKeyState[index] && !m_previousKeyState[index];
}

bool InputManager::wasKeyReleased(Key key) const {
	const auto index = static_cast<size_t>(key);
	return index < MAX_KEYS && !m_currentKeyState[index] && m_previousKeyState[index];
}

}