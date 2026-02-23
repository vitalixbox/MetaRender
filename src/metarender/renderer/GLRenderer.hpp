#pragma once

#include "IRenderer.hpp"

namespace metarender {

class GLRenderer : public IRenderer {
public:
	GLRenderer();
	~GLRenderer() override;

	void initialize(Window& window) override;
	void resize() override;
	void perspective(float fovY, float aspect, float nearZ, float farZ) override;

private:
	Window* m_window = nullptr;
};

}