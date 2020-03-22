#include "MyHandler.h"

#include "GL/gl.h"

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540
#define WINDOW_DEPTH_BYTES 3

#define PIXEL_RED_INDEX 0
#define PIXEL_GREEN_INDEX 1
#define PIXEL_BLUE_INDEX 2

void MyHandler::setup() {
	this->pixels.resize(WINDOW_WIDTH * WINDOW_HEIGHT * WINDOW_DEPTH_BYTES);

	for (int x = 0; x < WINDOW_WIDTH; x++) {
		for (int y = 0; y < WINDOW_HEIGHT; y++) {
			unsigned int pixelIndex = WINDOW_DEPTH_BYTES * (y * WINDOW_WIDTH + x);

			this->pixels[pixelIndex + PIXEL_RED_INDEX] = 1;
			this->pixels[pixelIndex + PIXEL_GREEN_INDEX] = 0.5;
			this->pixels[pixelIndex + PIXEL_BLUE_INDEX] = 0;
		}
	}

	glClearColor(0, 0, 0.5, 1);

	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &(this->textureHandle));
	glBindTexture(GL_TEXTURE_2D, this->textureHandle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_FLOAT, this->pixels.data());
}

int i = 0;

void MyHandler::render() {
	this->pixels[++i] = 0;
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGB, GL_FLOAT, this->pixels.data());

	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_QUADS);

	glTexCoord2f(0, 0);
	glVertex2f(-1, 1);

	glTexCoord2f(0, 1);
	glVertex2f(-1, -1);

	glTexCoord2f(1, 1);
	glVertex2f(1, -1);

	glTexCoord2f(1, 0);
	glVertex2f(1, 1);

	glEnd();
}

void MyHandler::clean() {
	this->pixels.clear();

	glDeleteTextures(1, &(this->textureHandle));
}
