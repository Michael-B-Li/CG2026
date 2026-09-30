#include "ColourSpectrumRenderer.h"
#include <cmath>

void ColourSpectrumRenderer::draw(DrawingWindow &window) {
   window.clearPixels();

   // set up triangle
   const glm::vec2 v0(0, window.height - 1);                 // red bottom left
   const glm::vec2 v1(window.width / 2, 0);                  // green top centre
   const glm::vec2 v2(window.width - 1, window.height - 1);  // blue bottom right
   const glm::vec3 red(255, 0, 0);
   const glm::vec3 green(0, 255, 0);
   const glm::vec3 blue(0, 0, 255);

   for (size_t y = 0; y < window.height; y++) {
      // calculate how far down triangle we are
      const float progress = static_cast<float>(y) / (window.height - 1);
      // find boundary for this row
      const float leftX = v1.x + progress * (v0.x - v1.x);
      const float rightX = v1.x + progress * (v2.x - v1.x);
      // round to draw strictly inside triangle
      const int startX = static_cast<int>(std::ceil(leftX));
      const int endX = static_cast<int>(std::floor(rightX));

      for (int x = startX; x <= endX; x++) {
         const glm::vec3 weights = convertToBarycentricCoordinates(v0, v1, v2, glm::vec2(x, y)); // find distance to each of the 3 corners
         const glm::vec3 rgb = weights.z * red + weights.x * green + weights.y * blue; // mix rgb colours based on distance
         const uint32_t colour = (255 << 24) + (int(rgb.r) << 16) + (int(rgb.g) << 8) + int(rgb.b);
         window.setPixelColour(x, y, colour);
      }
   }
}

std::vector<float> interpolateSingleFloats(float from, float to, int numberOfValues) {
   if (numberOfValues <= 0) return {};
   if (numberOfValues == 1) return {from};

   std::vector<float> values(numberOfValues);
    // difference between each pair of neighbouring values. n values n-1 intervals
   const float step = (to - from) / (numberOfValues - 1);

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
   const glm::vec3 step = (to - from) / static_cast<float>(numberOfValues - 1);   

   for (int i = 0; i < numberOfValues; i++) {
      values[i] = from + (static_cast<float>(i)*step);
   }
   return values;
}