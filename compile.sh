g++ -std=c++11 -Wall -Wextra -I./source -o ObjectTest \
./setup.cpp \
./source/MyHandler/MyHandler.cpp \
./source/SDLGLProgram/SDLGLProgram.cpp \
-lSDL -lGL -lpthread
