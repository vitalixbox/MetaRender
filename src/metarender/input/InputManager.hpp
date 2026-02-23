#pragma once

#include "KeyCodes.hpp"
#include <array>

namespace metarender {

class Window;

class InputManager {
public:
	explicit InputManager(Window& window);
	~InputManager();

	void update();

	// Keyboard state
	[[nodiscard]] bool isKeyDown(Key key) const;
	[[nodiscard]] bool isKeyUp(Key key) const;
	[[nodiscard]] bool wasKeyPressed(Key key) const;   // True only on frame key went down
	[[nodiscard]] bool wasKeyReleased(Key key) const;  // True only on frame key went up

private:
    Window& m_window;

	// Keyboard state
	static constexpr size_t MAX_KEYS = 512;
	std::array<bool, MAX_KEYS> m_currentKeyState{};
	std::array<bool, MAX_KEYS> m_previousKeyState{};
};

}