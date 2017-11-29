/*
Author: Chris Robertson https://github.com/electronicsleep
Date: 11/27/2017
Purpose: C++ and SDL2
Released under the BSD license
*/

#include <SDL2/SDL.h>
#include <iostream>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

using namespace std;


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
            printMsg("Error:CreateTextureFromSurface");
            exit(1);
        }
    } else {
        printMsg("Error:LoadBMP: " + file);
        exit(1);
    }
    return texture;
}


int main(int argc, char* argv[]) {

    string errorMsg = "";

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

    for (int i = 0; i < 50; ++i){
        SDL_RenderClear(ren);
        if (i % 3 == 0)
            SDL_RenderCopy(ren, tex, NULL, NULL);
        else if (i % 3 == 1)
            SDL_RenderCopy(ren, tex2, NULL, NULL);
        else
            SDL_RenderCopy(ren, tex3, NULL, NULL);
        printMsg("Result: " + to_string(i % 3));
        SDL_RenderPresent(ren);
        printMsg("Loop: " + to_string(i));
        SDL_Delay(100);
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
