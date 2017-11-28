
all: test

test: run1

run1:
	g++ ElectronicSleep.cpp -o ElectronicSleep -Wall -lSDL2main -lSDL2 -lGL -lglut -lGLEW
