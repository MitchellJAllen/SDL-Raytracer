COMPILE_FLAGS := -std=c++11 -pedantic -Wall -Wextra -Weffc++ -Isource
LINK_FLAGS := -std=c++11 -pedantic -Wall -Wextra -Weffc++ -pthread -lSDL -lGL

all: raytracer

raytracer: setup.o SDLGLProgram.o MyHandler.o
	g++ $(LINK_FLAGS) -o $@ $^

setup.o: setup.cpp source/SDLGLProgram/SDLGLProgram.h source/MyHandler/MyHandler.h source/SDLGLHandler/SDLGLHandler.h
	g++ -c $(COMPILE_FLAGS) -o $@ setup.cpp

SDLGLProgram.o: source/SDLGLProgram/SDLGLProgram.cpp source/SDLGLProgram/SDLGLProgram.h source/SDLGLHandler/SDLGLHandler.h
	g++ -c $(COMPILE_FLAGS) -o $@ source/SDLGLProgram/SDLGLProgram.cpp

MyHandler.o: source/MyHandler/MyHandler.cpp source/MyHandler/MyHandler.h source/SDLGLHandler/SDLGLHandler.h
	g++ -c $(COMPILE_FLAGS) -o $@ source/MyHandler/MyHandler.cpp

clean:
	rm *.o; rm raytracer
