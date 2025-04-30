#include <stdio.h>
#include <SDL.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int view(int argc, char *argv[]) {
    SDL_Window *window = NULL;

    SDL_Surface* screenSurface = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init: %s\n", SDL_GetError());
    } else {
        window = SDL_CreateWindow("Yukon Solitare", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL) {
            printf("SDL_CreateWindow: %s\n", SDL_GetError());
        }
    }


    return 0;
}
