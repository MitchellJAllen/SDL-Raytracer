#include "MyHandler.h"

#include <GL/gl.h>
#include <pthread.h>
#include <unistd.h>

#include <vector>

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 540
#define WINDOW_DEPTH_BYTES 3

#define PIXEL_RED_INDEX 0
#define PIXEL_GREEN_INDEX 1
#define PIXEL_BLUE_INDEX 2

void* writeToPixels(void* arg) {
	std::vector<float>& pixels = *((std::vector<float>*)arg);

	for (int y = 0; y < WINDOW_HEIGHT; y++) {
		for (int x = 0; x < WINDOW_WIDTH; x++) {
			unsigned int pixelIndex = WINDOW_DEPTH_BYTES * (y * WINDOW_WIDTH + x);

			pixels[pixelIndex + PIXEL_RED_INDEX] = 1;
			pixels[pixelIndex + PIXEL_GREEN_INDEX] = 0;
			pixels[pixelIndex + PIXEL_BLUE_INDEX] = 1;
		}

		usleep(1000); // 1 ms
	}

	pthread_exit(NULL);
}

void MyHandler::setup() {
	this->pixels.resize(WINDOW_WIDTH * WINDOW_HEIGHT * WINDOW_DEPTH_BYTES);

	for (int y = 0; y < WINDOW_HEIGHT; y++) {
		for (int x = 0; x < WINDOW_WIDTH; x++) {
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

	pthread_create(&(this->writeThread), NULL, writeToPixels, &(this->pixels));
}

void MyHandler::render() {
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
	pthread_cancel(this->writeThread);

	this->pixels.clear();

	glDeleteTextures(1, &(this->textureHandle));
}
