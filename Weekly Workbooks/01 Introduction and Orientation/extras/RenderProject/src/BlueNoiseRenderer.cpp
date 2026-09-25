#include "BlueNoiseRenderer.h"

void BlueNoiseRenderer::draw(DrawingWindow &window) {
	window.clearPixels();
	for (size_t y = 0; y < window.height; y++) {
		for (size_t x = 0; x < window.width; x++) {
			uint32_t blue = rand() % 256;
			uint32_t colour = (255u << 24) | blue;
			window.setPixelColour(x, y, colour);
		}
	}
}
