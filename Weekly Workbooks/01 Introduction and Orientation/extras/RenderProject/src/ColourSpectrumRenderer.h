#pragma once

#include "Renderer.h"
#include <vector>

class ColourSpectrumRenderer: public Renderer {
   public:
      void draw(DrawingWindow &window) override;
};

std::vector<float> interpolateSingleFloats(float from, float to, int numberOfValues);
