#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_mixer.h>

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

int main(){

    //Checks if SDL initialized
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not be initialized!\nSDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    //Checks if SDL2-mixer initialized
    if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 4096) == -1){
        printf("SDL2_mixer could not be initialized!\nSDL_Error: %s", SDL_GetError());
        return 1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("Audio player",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);

    //If window isn't created
    if (!window) {
        printf("Window could not be created!\nSDL_Error: %s\n", SDL_GetError());
    }

    //Create rendered
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        printf("Renderer could not be created!\n SDL_Error: %s\n", SDL_GetError());
    }

    bool quit = false;

    while (!quit) {

    }

    // Quit SDL2_mixer
    Mix_CloseAudio();

    // Quit SDL
    SDL_Quit();

    return 0;
}