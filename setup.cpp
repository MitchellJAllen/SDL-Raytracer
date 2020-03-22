#include "Program/Program.h"
#include "SDLGLProgram/SDLGLProgram.h"
#include "MyHandler/MyHandler.h"

#include "GL/gl.h"

int runProgram(Program& program) {
	return program.run();
}

int main() {
	SDLGLProgram myProgram;
	myProgram.setWindowTitle("SDL OpenGL C++ Object Test");
	myProgram.setWindowDimensions(960, 540);
	myProgram.setWindowFramesPerSecond(60);

	MyHandler myOpenGLHandler;
	myProgram.setSDLGLHandler(myOpenGLHandler);

	return runProgram(myProgram);
}