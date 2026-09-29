#include "ColourSpectrumRenderer.h"

void ColourSpectrumRenderer::draw(DrawingWindow &window) {
   window.clearPixels();
   // interpolates one brightness value per column, white to black
   std::vector<float> gradientRow = interpolateSingleFloats(255.0f, 0.0f, window.width);
   for (size_t y = 0; y < window.height; y++) {
      for (size_t x = 0; x < window.width; x++) {
         int grey = int(gradientRow[x]);
         // equal rgb give greyscale with alpha 255 makes it fully opaque
         uint32_t colour = (255 << 24) + (grey << 16) + (grey << 8) + grey;
         window.setPixelColour(x, y, colour);
      }
   }
}

std::vector<float> interpolateSingleFloats(float from, float to, int numberOfValues) {
   if (numberOfValues <= 0) return {};
   if (numberOfValues == 1) return {from};

   std::vector<float> values(numberOfValues);
    // difference between each pair of neighbouring values. n values n-1 intervals
   float step = (to - from) / (numberOfValues - 1);

   for (int i = 0; i < numberOfValues; i++) {
      values[i] = from + (i*step); // fill vector by adding increasing multiple of step to starting value
   }
   return values;
}

// this function interpolates 3 values compared to the above which does a single value
std::vector<glm::vec3> interpolateThreeElementValues(glm::vec3 from, glm::vec3 to, int numberOfValues){
   if (numberOfValues <= 0) return {};
   if (numberOfValues == 1) return {from};

   std::vector<glm::vec3> values(numberOfValues);
   glm::vec3 step = (to - from) / static_cast<float>(numberOfValues - 1);   

   for (int i = 0; i < numberOfValues; i++) {
      values[i] = from + (static_cast<float>(i)*step);
   }
   return values;
}