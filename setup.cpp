#include "SDLGLProgram/SDLGLProgram.h"
#include "MyHandler/MyHandler.h"

int main() {
	SDLGLProgram myProgram;
	myProgram.setWindowTitle("SDL OpenGL Raytracer");
	myProgram.setWindowDimensions(960, 540);
	myProgram.setWindowFramesPerSecond(60);

	MyHandler myOpenGLHandler;
	myProgram.setSDLGLHandler(myOpenGLHandler);

	return myProgram.run();
}
