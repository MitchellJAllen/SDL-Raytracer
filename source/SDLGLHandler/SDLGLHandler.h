#ifndef __SDLGLHANDLER_H__
#define __SDLGLHANDLER_H__

class SDLGLHandler {
public:

	virtual void setup() = 0;
	virtual void render() = 0;
	virtual void clean() = 0;
};

#endif
