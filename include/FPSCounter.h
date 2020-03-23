#ifndef FPSCOUNTER_H /* Include guard */
#define FPSCOUNTER_H

#include <SDL2/SDL.h>

// How many frames time values to keep
// The higher the value the smoother the result is...
// Don't make it 0 or less :)
#define FRAME_VALUES 100

class FPSCounter
{
private:
	// An array to store frame times:
	Uint32 _frameTimes[FRAME_VALUES];

	// Last calculated SDL_GetTicks
	Uint32 _frameTimeLast;

	// total frames rendered
	Uint32 _frameCount;

	// the value you want
	float _framesPerSecond;

public:
	// This function gets called once on startup.
	void fpsInit();
	void fpsThink();
	float getAverageFramesPerSecond();
	float getLastFramesPerSecond();
};

#endif