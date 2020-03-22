#ifndef __MYHANDLER_H__
#define __MYHANDLER_H__

#include "SDLGLHandler/SDLGLHandler.h"

#include <thread>
#include <vector>

class MyHandler : public SDLGLHandler {
private:

	static const unsigned short windowWidth;
	static const unsigned short windowHeight;
	static const unsigned short windowDepthInBytes;

	static const unsigned int pixelRedIndex;
	static const unsigned int pixelGreenIndex;
	static const unsigned int pixelBlueIndex;

	std::vector<float> pixels;
	std::thread writeThread;
	unsigned int textureHandle;

public:

	MyHandler();

	virtual void setup();
	virtual void render();
	virtual void clean();
};

#endif
