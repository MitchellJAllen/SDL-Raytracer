#include "MyHandler.h"

#include <GL/gl.h>
#include <pthread.h>
#include <unistd.h>

#include <vector>

const unsigned short MyHandler::windowWidth = 960;
const unsigned short MyHandler::windowHeight = 540;
const unsigned short MyHandler::windowDepthInBytes = 3;

const unsigned int MyHandler::pixelRedIndex = 0;
const unsigned int MyHandler::pixelGreenIndex = 1;
const unsigned int MyHandler::pixelBlueIndex = 2;

void* writeToPixels(void* arg) {
	const unsigned short windowWidth = 960;
	const unsigned short windowHeight = 540;
	const unsigned short windowDepthInBytes = 3;

	const unsigned int pixelRedIndex = 0;
	const unsigned int pixelGreenIndex = 1;
	const unsigned int pixelBlueIndex = 2;

	std::vector<float>& pixels = *((std::vector<float>*)arg);

	for (int y = 0; y < windowHeight; y++) {
		for (int x = 0; x < windowWidth; x++) {
			unsigned int pixelIndex = windowDepthInBytes * (y * windowWidth + x);

			pixels[pixelIndex + pixelRedIndex] = 1;
			pixels[pixelIndex + pixelGreenIndex] = 0;
			pixels[pixelIndex + pixelBlueIndex] = 1;
		}

		usleep(1000); // 1 ms
	}

	pthread_exit(NULL);
}

void MyHandler::setup() {
	const unsigned int pixelRedIndex = 0;
	const unsigned int pixelGreenIndex = 1;
	const unsigned int pixelBlueIndex = 2;

	this->pixels.resize(windowWidth * windowHeight * windowDepthInBytes);

	for (int y = 0; y < windowHeight; y++) {
		for (int x = 0; x < windowWidth; x++) {
			unsigned int pixelIndex = windowDepthInBytes * (y * windowWidth + x);

			this->pixels[pixelIndex + pixelRedIndex] = 1;
			this->pixels[pixelIndex + pixelGreenIndex] = 0.5;
			this->pixels[pixelIndex + pixelBlueIndex] = 0;
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

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, windowWidth, windowHeight, 0, GL_RGB, GL_FLOAT, this->pixels.data());

	pthread_create(&(this->writeThread), NULL, writeToPixels, &(this->pixels));
}

void MyHandler::render() {
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, windowWidth, windowHeight, GL_RGB, GL_FLOAT, this->pixels.data());

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
