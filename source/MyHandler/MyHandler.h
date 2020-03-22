#ifndef __MYHANDLER_H__
#define __MYHANDLER_H__

#include "../SDLGLHandler/SDLGLHandler.h"

#include <pthread.h>

#include <vector>

class MyHandler : public SDLGLHandler {
private:

	std::vector<float> pixels;
	unsigned int textureHandle;
	pthread_t writeThread;

public:

	void setup();
	void render();
	void clean();
};

#endif
