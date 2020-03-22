#ifndef __MYHANDLER_H__
#define __MYHANDLER_H__

#include "../SDLGLHandler/SDLGLHandler.h"

#include <vector>

class MyHandler : public SDLGLHandler {
private:
	std::vector<float> pixels;
	unsigned int textureHandle;

public:

	void setup();
	void render();
	void clean();
};

#endif
