#include "Config.hpp"

#include <metarender/log/Log.hpp>
#include <fstream>
#include <sstream>

namespace metarender {

Config::Config(const std::string& filepath)
	: m_filepath(filepath) {
	reload();
}

void Config::reload() {
	std::fstream file(m_filepath);
	if (!file.is_open()) {
		throw std::runtime_error("Config file not found: " + m_filepath);
	}

	file >> m_data;
}

const nlohmann::json* Config::navigate(const std::string& key) const {
	const nlohmann::json* current = &m_data;

	std::istringstream stream(key);
	std::string token;

	while (std::getline(stream, token, '.')) {
		if (!current->contains(token)) {
			return nullptr;
		}
		current = &(*current)[token];
	}

	return current;
}

std::string Config::getString(const std::string& key, const std::string& defaultValue) const {
	const auto* value = navigate(key);
	if (value && value->is_string()) {
		return value->get<std::string>();
	}
	return defaultValue;
}

int Config::getInt(const std::string& key, const int defaultValue) const {
	const auto* value = navigate(key);
	if (value && value->is_number_integer()) {
		return value->get<int>();
	}
	return defaultValue;
}

float Config::getFloat(const std::string& key, const float defaultValue) const {
	const auto* value = navigate(key);
	if (value && value->is_number_float()) {
		return value->get<float>();
	}
	return defaultValue;
}

bool Config::getBool(const std::string& key, const bool defaultValue) const {
	const auto* value = navigate(key);
	if (value && value->is_boolean()) {
		return value->get<bool>();
	}
	return defaultValue;
}

bool Config::has(const std::string& key) const {
	return navigate(key) != nullptr;
}

}
