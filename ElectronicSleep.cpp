/*
Author: Chris Robertson https://github.com/electronicsleep
Date: 11/27/2017
Purpose: C++ and SDL2
Released under the BSD license
*/

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

using namespace std;

int main(int argc, char* argv[]) {

    SDL_Window *window;

    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(
        "SDL2",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_OPENGL
    );

    if (window == NULL) {
        printf("Could not create window: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == NULL) {
        SDL_DestroyWindow(window);
        printf("SDL_CreateRenderer Error: %s ", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Surface *bmp = SDL_LoadBMP("Images/es1.bmp");
    if (bmp == NULL){
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(window);
        printf("SDL LoadBMP Error %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if (tex == NULL){
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(window);
        printf("SDL CreateTextureFromSurface Error %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }


    SDL_Surface *bmp2 = SDL_LoadBMP("Images/es2.bmp");
    if (bmp2 == NULL)    {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(window);
        printf("SDL LoadBMP Error %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Texture *tex2 = SDL_CreateTextureFromSurface(ren, bmp2);
    SDL_FreeSurface(bmp2);
    if (tex == NULL){
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(window);
        printf("SDL CreateTextureFromSurface Error %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Surface *bmp3 = SDL_LoadBMP("Images/es3.bmp");
    if (bmp2 == NULL)    {
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(window);
        printf("SDL LoadBMP Error %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Texture *tex3 = SDL_CreateTextureFromSurface(ren, bmp3);
    SDL_FreeSurface(bmp3);
    if (tex == NULL){
        SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(window);
        printf("SDL CreateTextureFromSurface Error %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    for (int i = 0; i < 50; ++i){
        SDL_RenderClear(ren);
        if (i % 3 == 0)
            SDL_RenderCopy(ren, tex, NULL, NULL);
        else if (i % 3 == 1)
            SDL_RenderCopy(ren, tex2, NULL, NULL);
        else
            SDL_RenderCopy(ren, tex3, NULL, NULL);
        //printf("Result: %d\n", i % 3 == 0);
        SDL_RenderPresent(ren);
        //printf("Loop Delay: %d\n", i);
        SDL_Delay(100);
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
