#include "Sandbox.hpp"

#include <metarender/log/Log.hpp>
#include <metarender/renderer/IRenderer.hpp>
#include <glad/glad.h>

namespace metarender::scenes {

void Sandbox::onEnter() {
}

void Sandbox::onRender() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

}