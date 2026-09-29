#include "ColourSpectrumRenderer.h"

void ColourSpectrumRenderer::draw(DrawingWindow &window) {
   window.clearPixels();
   glm::vec3 topLeft(255, 0, 0);       // red
   glm::vec3 topRight(0, 0, 255);      // blue
   glm::vec3 bottomRight(0, 255, 0);   // green
   glm::vec3 bottomLeft(255, 255, 0);  // yellow

   // interpolate down the left and right edges of the window
   std::vector<glm::vec3> leftColumn = interpolateThreeElementValues(topLeft, bottomLeft, window.height);
   std::vector<glm::vec3> rightColumn = interpolateThreeElementValues(topRight, bottomRight, window.height);

   for (size_t y = 0; y < window.height; y++) {
      // interpolate across this row between its two edge colours
      std::vector<glm::vec3> gradientRow = interpolateThreeElementValues(leftColumn[y], rightColumn[y], window.width);
      for (size_t x = 0; x < window.width; x++) {
         float red = gradientRow[x].x;
         float green = gradientRow[x].y;
         float blue = gradientRow[x].z;
         uint32_t colour = (255 << 24) + (int(red) << 16) + (int(green) << 8) + int(blue);
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