#pragma once

#include <string>
#include <nlohmann/json.hpp>

namespace metarender {

class Config {
public:
	explicit Config(const std::string& filepath);

	[[nodiscard]] std::string getString(const std::string& key, const std::string& defaultValue = "") const;
	[[nodiscard]] int getInt(const std::string& key, const int defaultValue = 0) const;
	[[nodiscard]] float getFloat(const std::string& key, const float defaultValue = 0.0f) const;
	[[nodiscard]] bool getBool(const std::string& key, const bool defaultValue = false) const;
	[[nodiscard]] bool has(const std::string& key) const;

	void reload();
private:
	[[nodiscard]] const nlohmann::json* navigate(const std::string& key) const;

	std::string m_filepath;
	nlohmann::json m_data;
};

}