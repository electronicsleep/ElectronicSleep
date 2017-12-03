/*
Author: Chris Robertson https://github.com/electronicsleep
Date: 11/27/2017
Purpose: C++ and SDL2
Released under the BSD license
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;


const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

static const char *DOZE_DREAM_MP3 = "Doze-Dream.mp3";


void printMsg(string msg){
    cout << msg << endl;
}


SDL_Texture* loadTexture(const std::string &file, SDL_Renderer *ren){
    SDL_Texture *texture = NULL;
    SDL_Surface *loadedImage = SDL_LoadBMP(file.c_str());
    if (loadedImage != NULL){
        texture = SDL_CreateTextureFromSurface(ren, loadedImage);
        SDL_FreeSurface(loadedImage);
        if (texture == NULL){
            printMsg("Error: CreateTextureFromSurface");
            exit(1);
        }
    } else {
        printMsg("Error: LoadBMP: " + file);
        exit(1);
    }
    return texture;
}


int main(int argc, char ** argv) {


    int x = 1;
    int y = 1;
    int loop = 0;
    bool quit = false;

    int result = 0;
    int flags = MIX_INIT_MP3;

    string errorMsg = "";

    SDL_Event event;


    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
	printMsg("Failed to init SDl2");
        exit(1);
    }

    if (flags != (result = Mix_Init(flags))) {
	printMsg("SDL2 Mixwer issue");
        errorMsg = Mix_GetError();
	printMsg("SDL2 Mix_Init " + errorMsg);
        exit(1);
    }

    // MP3
    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
    Mix_Music *music = Mix_LoadMUS(DOZE_DREAM_MP3);
    Mix_PlayMusic(music, 1);

    // WINDOW
    SDL_Window *window;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "Electronic Sleep C++ and SDL2",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL
    );

    if (window == NULL) {
        errorMsg = SDL_GetError();
        printMsg("Could not create window: " + errorMsg);
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL) {
        SDL_DestroyWindow(window);
        errorMsg = SDL_GetError();
        printMsg("SDL_CreateRenderer Error" + errorMsg);
        SDL_Quit();
        return 1;
    }


    SDL_Texture *tex = loadTexture("Images/es1.bmp", ren);
    SDL_Texture *tex2 = loadTexture("Images/es2.bmp", ren);
    SDL_Texture *tex3 = loadTexture("Images/es3.bmp", ren);

    SDL_Texture *tex4 = loadTexture("Images/sp1.bmp", ren);
    SDL_Texture *tex5 = loadTexture("Images/sp2.bmp", ren);
    SDL_Texture *tex6 = loadTexture("Images/sp3.bmp", ren);


    while (!quit)
    {
        SDL_Delay(20);
        SDL_PollEvent(&event);


        switch (event.type)
        {
        case SDL_QUIT:
            quit = true;
            printMsg("QUIT");
            break;

        case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
            case SDLK_LEFT:  x--; break;
            case SDLK_RIGHT: x++; break;
            case SDLK_UP:    y--; break;
            case SDLK_DOWN:  y++; break;
        }
        break;
        }

        loop++;
        SDL_RenderClear(ren);


        // BACKGROUND
        if (loop < 20)
            SDL_RenderCopy(ren, tex, NULL, NULL);
        else if (loop > 40)
            SDL_RenderCopy(ren, tex2, NULL, NULL);
        else
            SDL_RenderCopy(ren, tex3, NULL, NULL);


        int offset = 0;
        if (loop > 50)
            offset = 10;
        else
            offset = 50;

        for (int i = 0; i < 1000; i = i + 10) {
            if (loop % 3 == 0) {
                SDL_Rect dstrect = { i+offset, i, 64, 64 };
                SDL_RenderCopy(ren, tex4, NULL, &dstrect);
            } else if (loop % 1 == 0) {
                SDL_Rect dstrect2 = { i, i+offset+20, 64, 64 };
                SDL_RenderCopy(ren, tex5, NULL, &dstrect2);
            } else {
                SDL_Rect dstrect3 = { i+offset+50, i, 64, 64 };
                SDL_RenderCopy(ren, tex6, NULL, &dstrect3);
            }
        }


        printMsg("Result: " + to_string(loop % 3));

        if (loop > 100)
            loop = 0;

        SDL_Rect dstrect2 = { x, y, 64, 64 };
        SDL_RenderCopy(ren, tex4, NULL, &dstrect2);
        SDL_RenderPresent(ren);

        printMsg("Loop: " + to_string(loop));
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);

    Mix_FreeMusic(music);

    SDL_Quit();
    return 0;
}
