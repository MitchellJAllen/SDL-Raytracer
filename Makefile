COMPILE_FLAGS := -std=c++11 -Wall -Wextra -Isource
LINK_FLAGS := -pthread -lSDL -lGL

all: raytracer

raytracer: setup.o SDLGLProgram.o MyHandler.o
	g++ $(LINK_FLAGS) -o $@ $^

setup.o:
	g++ -c $(COMPILE_FLAGS) -o $@ setup.cpp

SDLGLProgram.o:
	g++ -c $(COMPILE_FLAGS) -o $@ source/SDLGLProgram/SDLGLProgram.cpp

MyHandler.o:
	g++ -c $(COMPILE_FLAGS) -o $@ source/MyHandler/MyHandler.cpp

clean:
	rm *.o; rm raytracer
