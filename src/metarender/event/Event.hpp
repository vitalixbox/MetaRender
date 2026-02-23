#pragma once

#include <cstdint>

namespace metarender {

enum class EventCategory : uint32_t {
	None		= 0,
	Application = 1 << 0,
	Input		= 1 << 1,
	Keyboard	= 1 << 2,
	Mouse		= 1 << 3,
	Window		= 1 << 4
};

inline EventCategory operator|(EventCategory a, EventCategory b) {
	return static_cast<EventCategory>(
		static_cast<uint32_t>(a) | static_cast<uint32_t>(b)
	);
}

inline bool operator&(EventCategory a, EventCategory b) {
	return (static_cast<uint32_t>(a) & static_cast<uint32_t>(b)) != 0;
}

class Event {
public:
	virtual ~Event() = default;

	[[nodiscard]] virtual const char* getName() const = 0;
	[[nodiscard]] virtual EventCategory getCategory() const = 0;

	[[nodiscard]] virtual bool isInCategory(EventCategory category) const {
		return getCategory() & category;
	}

	bool handled = false;
};

#define METARENDER_EVENT_CLASS(name, category)					\
	[[nodiscard]] const char* getName() const override {		\
		return #name;											\
	}															\
	[[nodiscard]] EventCategory getCategory() const override {	\
		return category;										\
	}															\

}