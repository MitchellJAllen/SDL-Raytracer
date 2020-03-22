#include "SDLGLProgram.h"

#include <SDL/SDL.h>

#include <iostream>

const char* SDLGLProgram::defaultWindowTitle = "SDL GL Program";
const unsigned short SDLGLProgram::defaultWindowWidth = 640;
const unsigned short SDLGLProgram::defaultWindowHeight = 480;
const unsigned short SDLGLProgram::defaultWindowFramesPerSecond = 60;

SDLGLProgram::SDLGLProgram():
	handler(nullptr),
	windowTitle(defaultWindowTitle),
	windowWidth(defaultWindowWidth),
	windowHeight(defaultWindowHeight),
	windowFramesPerSecond(defaultWindowFramesPerSecond)
{
}

int SDLGLProgram::run() {
	static const int errorNone = 0;
	static const int errorNoHandler = 1;
	static const int errorSDLSetup = 2;
	static const int errorVideoSetup = 3;

	bool programQuit = false;
	SDL_Event event;

	if (this->handler == nullptr) {
		std::cerr << "Error: no OpenGL handler specified" << std::endl;
		return errorNoHandler;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "Error: unable to initialize SDL" << std::endl;
		return errorSDLSetup;
	}

	if (SDL_SetVideoMode(this->windowWidth, this->windowHeight, 32, SDL_OPENGL) == NULL) {
		std::cerr << "Error: unable to set SDL video mode" << std::endl;
		return errorVideoSetup;
	}

	SDL_WM_SetCaption(this->windowTitle, NULL);
	this->handler->setup();

	while (!programQuit) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				programQuit = true;
			}
		}

		this->handler->render();

		SDL_GL_SwapBuffers();
		SDL_Delay(1000 / this->windowFramesPerSecond);
	}

	this->handler->clean();
	SDL_Quit();

	return errorNone;
}

void SDLGLProgram::setSDLGLHandler(SDLGLHandler& handler) {
	this->handler = &handler;
}

void SDLGLProgram::setWindowTitle(const char* title) {
	this->windowTitle = title;
}

void SDLGLProgram::setWindowDimensions(int width, int height) {
	this->windowWidth = width;
	this->windowHeight = height;
}

void SDLGLProgram::setWindowFramesPerSecond(int framesPerSecond) {
	this->windowFramesPerSecond = framesPerSecond;
}
