#ifndef FPSCOUNTER_H /* Include guard */
#define FPSCOUNTER_H

#include "Common.h"

// How many frames time values to keep
// The higher the value the smoother the result is...
// Don't make it 0 or less :)
#define FRAME_VALUES 100
#define MILLISECOND_IN_SECOND 1000.F

class FPSCounter {
private:
  // An array to store frame times:
  Uint32 _frameTimes[FRAME_VALUES] = {}; // all elements 0 in C++;

  // Last calculated SDL_GetTicks
  Uint32 _frameTimeLast;

  // total frames rendered
  Uint32 _frameCount;

  // the value you want
  float _framesPerSecond;

public:
  // This function gets called once on startup.
  auto fpsInit() -> void;
  auto fpsThink() -> void;
  auto getAverageFramesPerSecond() -> float;
  auto getLastFramesPerSecond() -> float;
};

#endif
