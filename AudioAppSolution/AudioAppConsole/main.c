#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_mixer.h>

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define MONO 1
#define STEREO 2
#define CD 44100
#define DVD 48000
#define HiRes1 96000
#define HiRes2 192000

#define TrackMP3 "./assets/Stray Kids - CEREMONY.mp3"
#define TrackFLAC "./assets/04. The Cranberries - Zombie.flac"

//Глобальная переменная для текущей песни
Mix_Music* track;

//Function to test playback of MP3, FLAC
void TestPlayback(const char *trackName) {
    if (!Mix_PlayingMusic()) {
        //If music isn't playing
        track = Mix_LoadMUS(trackName);
        if (!track) {
            printf("Track %s could not be loaded!\nSDL_Error: %s\n", trackName, SDL_GetError());
            return 1;
        }
        Mix_PlayMusic(track, 0);
    }
}

int main(){

    //Checks if SDL initialized
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not be initialized!\nSDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    //Checks audio formats
    if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG | MIX_INIT_MID | MIX_INIT_OPUS) == 0) {
        printf("SDL2_mixer does not support one of the formats!\nSDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    //Checks if SDL2-mixer initialized
    if (Mix_OpenAudio(DVD, MIX_DEFAULT_FORMAT, STEREO, 4096) == -1){
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

    bool quit = false; //Flag for quitting

    Mix_VolumeMusic(30); //30 volume for all channels

    //Write code inside of this loop
    while (!quit) {
        SDL_Event e;

        // Wait indefinitely for the next available event
        SDL_WaitEvent(&e);

        // User requests quit
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }
        //If user presses a key
        else if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym) {
            //If space pressed
            case SDLK_SPACE:
                if (Mix_PausedMusic() == 1)
                    Mix_ResumeMusic();
                else
                    Mix_PauseMusic();
                break;

            }
        }

        TestPlayback(TrackMP3);
    }

    // Quit SDL2_mixer
    Mix_CloseAudio();

    // Deinitialize SDL2 Mix
    Mix_Quit();

    // Quit SDL
    SDL_Quit();

    return 0;
}