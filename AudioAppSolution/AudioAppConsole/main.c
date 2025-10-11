#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "Playlist.h"
#include "Songs.h"


#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define MONO 1
#define STEREO 2
#define CD 44100
#define DVD 48000
#define HiRes1 96000
#define HiRes2 192000


//#define TrackMP3 "./assets/Stray Kids - CEREMONY.mp3"
//#define TrackFLAC "./assets/04. The Cranberries - Zombie.flac"
#define TrackPlaylist1 "./assets/Stray Kids - CEREMONY.mp3"
#define TrackPlaylist2 "./assets/Taylor Swift - Blank Space.mp3"
#define TrackPlaylist3 "./assets/Ariana Grande - 7 rings.mp3"
#define TrackPlaylist4 "./assets/Stray Kids-Booster.mp3"
#define TrackPlaylist5 "./assets/Stray Kids - MEGAVERSE.mp3"
#define TrackPlaylist6 "./assets/Taylor Swift-Back To December (Taylor s Version).mp3"
#define TrackPlaylist7 "./assets/04. The Cranberries - Zombie.flac"


//Global variable for current song (for TestPlayback)
Mix_Music* track = NULL;
//Global variable for playlist (for TestPlaylist)
Playlist* playlist = NULL;

//Function to test playback of MP3, FLAC
//When finished playing, Mix_FreeMusic must be called at some point
//Note: calling FreeMusic can cause memory access violation (it can be solved by setting the track pointer to NULL after freeing (see Playlist.c)) 
void TestPlayback(const char *trackName) {
    if (!Mix_PlayingMusic()) {
        //If music isn't playing
        track = Mix_LoadMUS(trackName);
        if (!track) {
            printf("Track %s could not be loaded!\nSDL_Error: %s\n", trackName, SDL_GetError());
            return;
        }
        Mix_PlayMusic(track, 0);
    }
}

//Callback for automatically starting the next song
void nextPlaylistSongCallback() {
    if (playlist->isPlaying) {
        nextPlaylistSong(playlist);
    }
}

//Function to test Playlists
void TestPlaylist() {
    //If playlist isn't created yet
    if (!playlist) {
        //Create and start playing the playlist
        char* tracks[] = { TrackPlaylist1 , TrackPlaylist2, TrackPlaylist3, TrackPlaylist4, TrackPlaylist5, TrackPlaylist6, TrackPlaylist7 };
        playlist = createPlaylist(tracks, 7);
        startPlaylist(playlist);
        repeatPlaylist(playlist);
    }
    //If a song finishes playing (but the playlist continues), a callback is called to automatically start the next song
    //TODO: check if this call takes up stack memory
    Mix_HookMusicFinished((Mix_MusicFinishedCallback)nextPlaylistSongCallback);

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

    Mix_VolumeMusic(30); //30 volume for music

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
            //Checks what key has been pressed
            switch (e.key.keysym.sym) {
                //If space pressed
                case SDLK_SPACE:
                    if (Mix_PausedMusic() == 1) {
                        Mix_ResumeMusic();
                    }
                    else {
                        Mix_PauseMusic();
                    }
                    //If playlist music was halted, then space should allow playlist to start again
                    if (!playlist->isPlaying) {
                        playlist->isPlaying = true;
                        startPlaylist(playlist); //Maybe add index to function call to start playlist from any chosen index?
                    }
                    break;

                //Right arrow
                case SDLK_RIGHT:
                    nextPlaylistSong(playlist);
                    break;
                    
                //Left arrow
                case SDLK_LEFT:
                    playSongFromBeginningOrPrev(playlist);
                    break;
                //Up arrow
                case SDLK_UP:
                    increasePlaylistVolume(playlist);
                    break;

                //Down arrow
                case SDLK_DOWN:
                    decreasePlaylistVolume(playlist);
                    break;

            }
        }
        TestPlaylist(); //Test playlist functionality (can comment out)      
    }

    if (playlist) {
        clearPlaylist(playlist); //Free playlist memory if allocated
    }

    // Quit SDL2_mixer
    Mix_CloseAudio();

    // Deinitialize SDL2 Mix
    Mix_Quit();

    // Quit SDL
    SDL_Quit();

    return 0;
}