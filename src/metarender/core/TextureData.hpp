#pragma once
#include <vector>
#include <cstdint>

namespace metarender {

struct TextureData {
	unsigned char* data = nullptr;
	int width = 0;
	int height = 0;
	int channels = 0;
};

}