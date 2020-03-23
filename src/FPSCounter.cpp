#include "FPSCounter.h"

void FPSCounter::fpsInit() {

        // Set all frame times to 0ms.
        memset(_frameTimes, 0, sizeof(_frameTimes));
        _frameCount = 0;
        _framesPerSecond = 0;
        _frameTimeLast = SDL_GetTicks();
}

void FPSCounter::fpsThink() {

        Uint32 frametimesindex;
        Uint32 getticks;
        Uint32 count;
        Uint32 i;

        // frametimesindex is the position in the array. It ranges from 0 to FRAME_VALUES.
        // This value rotates back to 0 after it hits FRAME_VALUES.
        frametimesindex = _frameCount % FRAME_VALUES;
        // printf("_frameCount:  %d\n", _frameCount);
        // store the current time
        getticks = SDL_GetTicks();

        // save the frame time value
        _frameTimes[frametimesindex] = getticks - _frameTimeLast;

        // save the last frame time for the next fpsthink
        _frameTimeLast = getticks;

        // increment the frame count
        _frameCount++;

        // Work out the current framerate

        // The code below could be moved into another function if you don't need the value every frame.

        // I've included a test to see if the whole array has been written to or not. This will stop
        // strange values on the first few (FRAME_VALUES) frames.
        if (_frameCount < FRAME_VALUES) {

                count = _frameCount;

        } else {

                count = FRAME_VALUES;

        }

        // add up all the values and divide to get the average frame time.
        _framesPerSecond = 0;
        for (i = 0; i < count; i++) {

                _framesPerSecond += _frameTimes[i];

        }

        _framesPerSecond /= count;

        // now to make it an actual frames per second value...
        _framesPerSecond = 1000.f / _framesPerSecond;
}

float FPSCounter::getAverageFramesPerSecond()
{
	return _framesPerSecond;
}

float FPSCounter::getLastFramesPerSecond()
{
	return 1000.f / _frameTimes[_frameCount % FRAME_VALUES];
}