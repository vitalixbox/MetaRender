#include "Window.hpp"
#include <metarender/log/Log.hpp>
#include <metarender/core/ServiceLocator.hpp>
#include <metarender/event/EventBus.hpp>
#include <metarender/event/WindowEvents.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdexcept>

namespace metarender {

static bool s_glfwInitialized = false;

Window::Window(const CreateInfo& info) {
	initGLFW();
	createWindow(info);
	setupCallbacks();
}

Window::~Window() {
	if (m_window) {
		glfwDestroyWindow(m_window);
	}
}

void Window::initGLFW() {
	if (!s_glfwInitialized) {
		if (!glfwInit()) {
			throw std::runtime_error("Failed to initialize GLFW");
		}

		glfwSetErrorCallback([](int error, const char* description) {
			LOG_ERROR("GLFW Error. {}: {}", error, description);
		});

		s_glfwInitialized = true;
		LOG_INFO("GLFW initialized");
	}
}

void Window::createWindow(const CreateInfo& info) {
	m_width = info.width;
	m_height = info.height;
	m_vsync = info.vsync;

	glfwWindowHint(GLFW_RESIZABLE, info.resizable ? GLFW_TRUE : GLFW_FALSE);

	GLFWmonitor* monitor = info.fullscreen ? glfwGetPrimaryMonitor() : nullptr;
	m_window = glfwCreateWindow(m_width, m_height, info.title.c_str(), monitor, nullptr);
	if (!m_window) {
		throw std::runtime_error("Failed to create GLFW window");
	}
	glfwMakeContextCurrent(m_window);

	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		throw std::runtime_error("Failed to initialize GLAD");
	}

	setVSync(m_vsync);

	glfwSetWindowUserPointer(m_window, this);

	LOG_INFO("Window created: {}x{}", m_width, m_height);
	LOG_INFO("OpenGL Version: {}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
}

void Window::setupCallbacks() {
	glfwSetFramebufferSizeCallback(m_window, [](GLFWwindow* window, int width, int height) {
		auto* self = static_cast<Window*>(glfwGetWindowUserPointer(window));
		self->m_width = width;
		self->m_height = height;

		if (auto* eventBus = ServiceLocator::get<EventBus>()) {
			// TODO: Move usage of ServiceLocator::get to constructor and make eventBus* as a part of class
			eventBus->publish<WindowResizeEvent>(width, height);
		}
	});

	glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window) {
		if (auto* eventBus = ServiceLocator::get<EventBus>()) {
			eventBus->publish<WindowCloseEvent>();
		}
	});
}

void Window::pollEvents() {
	glfwPollEvents();
}

void Window::swapBuffers() {
	glfwSwapBuffers(m_window);
}

bool Window::shouldClose() const {
	return glfwWindowShouldClose(m_window);
}

void Window::setShouldClose(bool value) {
	glfwSetWindowShouldClose(m_window, value ? GLFW_TRUE : GLFW_FALSE);
}

float Window::getAspectRatio() const {
	return m_height > 0 ? static_cast<float>(m_width) / static_cast<float>(m_height) : 1.0f;
}

void Window::setVSync(bool enabled) {
	m_vsync = enabled;
	glfwSwapInterval(enabled ? 1 : 0);
}

}
