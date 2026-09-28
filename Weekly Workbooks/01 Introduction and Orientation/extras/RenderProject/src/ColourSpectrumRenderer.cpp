#include "ColourSpectrumRenderer.h"

void ColourSpectrumRenderer::draw(DrawingWindow &window) {
   window.clearPixels();
   // Write some drawing code in here !
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
