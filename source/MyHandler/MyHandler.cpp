#include "MyHandler.h"

#include <GL/gl.h>

#include <chrono>
#include <thread>
#include <vector>

const unsigned short MyHandler::windowWidth = 960;
const unsigned short MyHandler::windowHeight = 540;
const unsigned short MyHandler::windowDepthInBytes = 3;

const unsigned int MyHandler::pixelRedIndex = 0;
const unsigned int MyHandler::pixelGreenIndex = 1;
const unsigned int MyHandler::pixelBlueIndex = 2;

void writeToPixels(std::vector<float>& pixels) {
	const unsigned short windowWidth = 960;
	const unsigned short windowHeight = 540;
	const unsigned short windowDepthInBytes = 3;

	const unsigned int pixelRedIndex = 0;
	const unsigned int pixelGreenIndex = 1;
	const unsigned int pixelBlueIndex = 2;

	for (int y = 0; y < windowHeight; y++) {
		for (int x = 0; x < windowWidth; x++) {
			unsigned int pixelIndex = windowDepthInBytes * (y * windowWidth + x);

			pixels[pixelIndex + pixelRedIndex] = 0;
			pixels[pixelIndex + pixelGreenIndex] = 0;
			pixels[pixelIndex + pixelBlueIndex] = 0.5;
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	pthread_exit(NULL);
}

MyHandler::MyHandler():
	pixels(windowWidth * windowHeight * windowDepthInBytes, 0),
	writeThread(writeToPixels, std::ref(this->pixels))
{
}

void MyHandler::setup() {
	glClearColor(0, 0, 0.5, 1);

	glEnable(GL_TEXTURE_2D);

	glGenTextures(1, &(this->textureHandle));
	glBindTexture(GL_TEXTURE_2D, this->textureHandle);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, windowWidth, windowHeight, 0, GL_RGB, GL_FLOAT, this->pixels.data());
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
	this->pixels.clear();

	glDeleteTextures(1, &(this->textureHandle));
}
