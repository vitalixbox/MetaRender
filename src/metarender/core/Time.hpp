#pragma once

#include <chrono>

namespace metarender {

class Time {
public:
	using Clock = std::chrono::high_resolution_clock;
	using TimePoint = Clock::time_point;
	using Duration = std::chrono::duration<float>;

	Time();

	void update();

	[[nodiscard]] float getDeltaTime() const { return m_deltaTime; }
	[[nodiscard]] float getElapsedTime() const { return m_elapsedTime; }
	[[nodiscard]] uint64_t getFrameCount() const { return m_frameCount; }
	[[nodiscard]] float getFPS() const { return m_fps; }

private:
	TimePoint m_startTime;
	TimePoint m_lastFrameTime;

	float m_deltaTime = 0.0f;
	float m_elapsedTime = 0.0f;
	uint64_t m_frameCount = 0;

	// FPS calculation
	float m_fps = 0.0f;
	float m_fpsAccumulator = 0.0f;
	int m_fpsFrameCount = 0;
};

}