#include "AssetManager.hpp"

#include <string>
#include <stdexcept>

#include <SOIL2/SOIL2.h>

namespace metarender {

unsigned int AssetManager::loadTexture(const char* path) {
    unsigned int texture = SOIL_load_OGL_texture(
        path,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_INVERT_Y
    );

    if (texture == 0) {
		throw std::runtime_error("Failed to load texture: " + std::string(path));
	}

    return texture;
}

TextureData AssetManager::loadTextureData(const char* path) {
	TextureData textureData;

    textureData.data = SOIL_load_image(
        path,
        &textureData.width,
        &textureData.height,
        &textureData.channels,
        SOIL_LOAD_RGB
    );

    if (!textureData.data) {
		throw std::runtime_error("Failed to load texture: " + std::string(path));
	}

    return textureData;
}

}