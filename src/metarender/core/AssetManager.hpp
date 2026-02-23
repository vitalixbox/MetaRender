#pragma once

#include "TextureData.hpp"

namespace metarender {

class AssetManager {
public:
	unsigned int loadTexture(const char* path);
	TextureData loadTextureData(const char* path);

private:
};

}