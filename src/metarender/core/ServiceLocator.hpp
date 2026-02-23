#pragma once

#include <typeindex>
#include <unordered_map>
#include <cassert>

namespace metarender {

class ServiceLocator {
public:
	template<typename T>
	static void provide(T* service) {
		auto key = std::type_index(typeid(T));
		assert(s_services.find(key) == s_services.end() && "Service already provided");
		s_services[key] = service;
	}

	template<typename T>
	[[nodiscard]] static T* get() {
		auto it = s_services.find(std::type_index(typeid(T)));
		if (it != s_services.end()) {
			return static_cast<T*>(it->second);
		}
		return nullptr;
	}

	template<typename T>
	[[nodiscard]] static T* getRequired() {
		T* service = get<T>();
		assert(service != nullptr && "Service not found");
		return service;
	}

private:
	static inline std::unordered_map<std::type_index, void*> s_services;
};

}