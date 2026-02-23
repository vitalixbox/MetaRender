#pragma once

#include "Event.hpp"

namespace metarender {

class WindowResizeEvent : public Event {
public:
	WindowResizeEvent(int width, int height)
		: m_width(width), m_height(height) {
	}
	METARENDER_EVENT_CLASS(WindowResizeEvent, EventCategory::Window)

private:
	int m_width;
	int m_height;
};

class WindowCloseEvent : public Event {
public:
	METARENDER_EVENT_CLASS(WindowCloseEvent, EventCategory::Window)
};

}