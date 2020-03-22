#ifndef __SDLGLPROGRAM_H__
#define __SDLGLPROGRAM_H__

#include "../Program/Program.h"
#include "../SDLGLHandler/SDLGLHandler.h"

#define DEFAULT_TITLE "SDL GL Program"
#define DEFAULT_WIDTH 640
#define DEFAULT_HEIGHT 480
#define DEFAULT_FRAMES_PER_SECOND 60

class SDLGLProgram : public Program {
private:

	SDLGLHandler* handler {nullptr};
	const char* windowTitle {DEFAULT_TITLE};
	int windowWidth {DEFAULT_WIDTH};
	int windowHeight {DEFAULT_HEIGHT};
	int windowFramesPerSecond {DEFAULT_FRAMES_PER_SECOND};

public:

	int run();

	void setSDLGLHandler(SDLGLHandler& handler);
	void setWindowTitle(const char* title);
	void setWindowDimensions(int width, int height);
	void setWindowFramesPerSecond(int framesPerSecond);
};

#endif
