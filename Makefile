
all: test

test: run1

run1:
	g++ ElectronicSleep.cpp -o ElectronicSleep.out -std=c++0x -Wall -lSDL2main -lSDL2_mixer -lSDL2 -lGL -lglut -lGLEW
