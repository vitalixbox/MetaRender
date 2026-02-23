#pragma once

#include "Event.hpp"

#include <vector>
#include <unordered_map>
#include <typeindex>
#include <functional>

namespace metarender {

class EventBus {
public:
	using ListenerID = uint64_t;
	using EventCallback = std::function<void(Event&)>;

	template<typename EventType>
	ListenerID subscribe(std::function<void(EventType&)> callback) {
		static_assert(std::is_base_of_v<Event, EventType>,
			"EventType must derive from Event");

		const ListenerID id = m_nextListenerID++;
		const auto typeIndex = std::type_index(typeid(EventType));

		m_listeners[typeIndex].push_back({
			id,
			[callback](Event& e) {
				callback(static_cast<EventType&>(e));
			}
		});

		return id;
	}

	void unsubscribe(ListenerID id) {
		for (auto& [type, listeners] : m_listeners) {
			listeners.erase(
				std::remove_if(
					listeners.begin(), listeners.end(),
					[id](const Listener& l) { return l.id == id; }
				),
				listeners.end()
			);
		}
	}

	template<typename EventType, typename... Args>
	void publish(Args&&... args) {
		EventType event(std::forward<Args>(args)...);
		publishEvent(event);
	}

	void publishEvent(Event& event) {
		const auto typeIndex = std::type_index(typeid(event));
		auto it = m_listeners.find(typeIndex);
		if (it != m_listeners.end()) {
			for (auto& listener : it->second) {
				if (!event.handled) {
					listener.callback(event);
				}
			}
		}
	}

private:
	struct Listener {
		ListenerID id;
		EventCallback callback;
	};

	std::unordered_map<std::type_index, std::vector<Listener>> m_listeners;
	ListenerID m_nextListenerID = 1;
};

}