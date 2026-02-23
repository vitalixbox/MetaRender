#pragma once

namespace metarender {

class Window;

class IRenderer {
public:
	virtual ~IRenderer() = default;

	virtual void initialize(Window& window) = 0;
	virtual void resize() = 0;
	virtual void perspective(float fovY, float aspect, float nearZ, float farZ) = 0;
};

}