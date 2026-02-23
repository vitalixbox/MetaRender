#pragma once

#include <iostream>

namespace metarender {

class Log {
public:
	enum class Level { Trace, Debug, Info, Warn, Error };

	static void init() {
		s_initialized = true;
	}

	static void setLevel(Level level) {
		s_level = level;
	}

	template<typename... Args>
	static void log(Level level, const char* fmt, Args&&... args) {
		if (!s_initialized || level < s_level) return;

		std::cout << "[" << levelToString(level) << "] ";
		print(fmt, std::forward<Args>(args)...);
		std::cout << std::endl;
	}

private:
	static const char* levelToString(Level level) {
		switch (level) {
			case Level::Trace: return "TRACE";
			case Level::Debug: return "DEBUG";
			case Level::Info: return "INFO";
			case Level::Warn: return "WARN";
			case Level::Error: return "ERROR";
		default:
			return "?????";
		}
	}

	static void print(const char* fmt) {
		std::cout << fmt;
	}

	template<typename T, typename... Rest>
	static void print(const char* fmt, T&& value, Rest&&... rest) {
		while (*fmt){
			if (fmt[0] == '{' && fmt[1] != '\0' && fmt[1] == '}') {
				std::cout << std::forward<T>(value);
				print(fmt + 2, std::forward<Rest>(rest)...);
				return;
			}
			std::cout << *fmt++;
		}
	}

	static inline bool s_initialized = false;
	static inline Level s_level = Level::Info;
};

#define LOG_TRACE(...) ::metarender::Log::log(::metarender::Log::Level::Trace, __VA_ARGS__)
#define LOG_DEBUG(...) ::metarender::Log::log(::metarender::Log::Level::Debug, __VA_ARGS__)
#define LOG_INFO(...) ::metarender::Log::log(::metarender::Log::Level::Info, __VA_ARGS__)
#define LOG_WARN(...) ::metarender::Log::log(::metarender::Log::Level::Warn, __VA_ARGS__)
#define LOG_ERROR(...) ::metarender::Log::log(::metarender::Log::Level::Error, __VA_ARGS__)

}