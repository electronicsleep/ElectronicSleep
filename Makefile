# Detect OS
UNAME := $(shell uname)

# Build based on OS name
DetectOS:
	-@make $(UNAME)

Linux:
	g++ ElectronicSleep.cpp -o ElectronicSleep -std=c++17 -Wall -lSDL2main -lSDL2 -lSDL2_ttf

Darwin:
	# g++ ElectronicSleep.cpp -o ElectronicSleep -I/opt/homebrew/include -L/opt/homebrew/lib -std=c++17 -Wall -lSDL2main -lSDL2 -lSDL2_ttf
	g++ ElectronicSleep.cpp -o ElectronicSleep -I/opt/homebrew/include -L/opt/homebrew/lib -std=c++17 -Wall -lSDL2main -lSDL2_mixer -lSDL2 -lSDL2_ttf

run:
	./Electronicsleep
