#include "SDLGLProgram.h"

#include <SDL/SDL.h>

#include <iostream>

#define ERROR_NONE 0
#define ERROR_NO_HANDLER 1
#define ERROR_SDL_SETUP 2
#define ERROR_VIDEO_SETUP 3

int SDLGLProgram::run() {
	bool programQuit = false;
	SDL_Event event;

	if (this->handler == nullptr) {
		std::cerr << "Error: no OpenGL handler specified" << std::endl;
		return ERROR_NO_HANDLER;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "Error: unable to initialize SDL" << std::endl;
		return ERROR_SDL_SETUP;
	}

	if (SDL_SetVideoMode(this->windowWidth, this->windowHeight, 32, SDL_OPENGL) == NULL) {
		std::cerr << "Error: unable to set SDL video mode" << std::endl;
		return ERROR_VIDEO_SETUP;
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

	return ERROR_NONE;
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
