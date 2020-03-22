#ifndef __SDLGLPROGRAM_H__
#define __SDLGLPROGRAM_H__

#include "../SDLGLHandler/SDLGLHandler.h"

class SDLGLProgram {
private:

	static const char* defaultWindowTitle;
	static const unsigned short defaultWindowWidth;
	static const unsigned short defaultWindowHeight;
	static const unsigned short defaultWindowFramesPerSecond;

	SDLGLHandler* handler;
	const char* windowTitle;
	int windowWidth;
	int windowHeight;
	int windowFramesPerSecond;

public:

	SDLGLProgram();

	int run();

	void setSDLGLHandler(SDLGLHandler& handler);
	void setWindowTitle(const char* title);
	void setWindowDimensions(int width, int height);
	void setWindowFramesPerSecond(int framesPerSecond);
};

#endif
