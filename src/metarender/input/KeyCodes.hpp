#pragma once

#include <string_view>
#include <cstdint>
#include <array>

namespace metarender {

// Key codes (matching GLFW, but abstracted)
enum class Key : int32_t {
#define KEY(name, value) name = value,
#include "KeyCodes.inc"
#undef KEY
};

struct KeyUtil {
	static constexpr std::string_view toString(Key key) {
		switch (key) {
#define KEY(name, value) case Key::name: return #name;
#include "KeyCodes.inc"
#undef KEY
		default: return "Unknown";
		}
	}

	static constexpr auto AllKeys = [] {
		// count keys
		constexpr size_t count = [] {
			size_t c = 0;
#define KEY(name, value) ++c;
#include "KeyCodes.inc"
#undef KEY
			return c;
			}();

		std::array<Key, count> keys{};

		size_t i = 0;
#define KEY(name, value) keys[i++] = Key::name;
#include "KeyCodes.inc"
#undef KEY

		return keys;
		}();
};

enum class MouseButton : int32_t {
	Left = 0,
	Right = 1,
	Middle = 2,
	Button4 = 3,
	Button5 = 4,
	Button6 = 5,
	Button7 = 6,
	Button8 = 7
};

}