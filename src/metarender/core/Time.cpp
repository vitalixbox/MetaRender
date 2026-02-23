#include "Time.hpp"

namespace metarender {

Time::Time()
	: m_startTime(Clock::now())
	, m_lastFrameTime(m_startTime) {
}

void Time::update() {
	const TimePoint currentTime = Clock::now();

	m_deltaTime = Duration(currentTime - m_lastFrameTime).count();
	m_elapsedTime = Duration(currentTime - m_startTime).count();
	m_lastFrameTime = currentTime;
	m_frameCount++;

	// Calculate FPS (averaged over ~1 second)
	m_fpsAccumulator += m_deltaTime;
	m_fpsFrameCount++;
	if (m_fpsAccumulator >= 1.0f) {
		m_fps = static_cast<float>(m_fpsFrameCount) / m_fpsAccumulator;
		m_fpsAccumulator = 0.0f;
		m_fpsFrameCount = 0;
	}
}

}