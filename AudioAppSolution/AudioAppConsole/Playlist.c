#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <string.h>
#include "Playlist.h"
#include <Windows.h>

//Helper function to stop and free Music from a playlist
//static to not be available by other files
static void stopMusic(Playlist *playlist) {
    playlist->isPlaying = false;
    Mix_HaltMusic();
    if (playlist->currentTrack->music) {
        Mix_FreeMusic(playlist->currentTrack->music);
        playlist->currentTrack->music = NULL;
    }
}

//Helper function to play Music from a playlist
//static to not be available by other files
static void playMusic(Playlist* playlist) {
    playlist->startTime = SDL_GetTicks64();
    playlist->currentTrack->music = Mix_LoadMUS(playlist->tracks[playlist->currentTrackIndex]);
    Mix_PlayMusic(playlist->currentTrack->music, 0);
    playlist->isPlaying = true;
    strcpy_s(playlist->currentTrack->title, 100, playlist->tracks[playlist->currentTrackIndex]);
    printf("Position: %d\tIndex: %d\tSong: %s\n", playlist->currentTrackPosition, playlist->currentTrackIndex, playlist->currentTrack->title);
}

//Swap playlist indeces
static void swapIndeces(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


//Creates a playlist from audio paths passed into the function in an array
//Requires track count to be passed to work with tracks array
//Returns pointer to created playlist (call clearPlaylist to free memory!) or NULL if the playlist fails to be created (Exceeds number of max tracks allowed or path length)
Playlist* createPlaylist(char **tracks, int trackCount) {
    //Check if track count passed is bigger, than the max allowed
    if (trackCount > MAX_TRACKS) {
        printf("Cannot create a playlist with more than 100 tracks");
        return NULL;
    }
    //Check if the path length of each track passed is bigger, than the max allowed 
    for (size_t i = 0; i < trackCount; i++)
    {
        if (sizeof(tracks[i]) > MAX_PATH_LENGTH) {
            printf("Sound path cannot exceed 256 symbols");
            return NULL;
        }
    }

    //Playlist memory allocation
    Playlist* playlist = (Playlist*)malloc(sizeof(Playlist));
    if (!playlist) {
        printf("Error while allocating memory for playlist");
        return NULL;
    }

    //Song memory allocation
    Song *song = (Song *)malloc(sizeof(Song));
    if (!song) {
        printf("Error while allocating memory for a song");
        return NULL;
    }

    //Initialization
    for(int i = 0; i < MAX_TRACKS; i++){
        playlist->trackIndeces[i] = i;
    }

    playlist->currentTrack = song;
    playlist->currentTrack->music = NULL;
    playlist->currentTrackIndex = -1;
    playlist->currentTrackPosition = -1;
    playlist->trackCount = trackCount;
    playlist->isRepeat = false;
    playlist->isShuffled = false;
    playlist->volume = 50;
    Mix_VolumeMusic(playlist->volume);

    //Write into the tracks array
    for (size_t i = 0; i < trackCount; i++)
    {
        strcpy_s(playlist->tracks[i], MAX_PATH_LENGTH, tracks[i]);
    }
    return playlist;
}

//Start playing playlist
void startPlaylist(Playlist *playlist, bool loop, bool shuffle) {
    //Free up any music that may be currently playing
    stopMusic(playlist);
    //Check if should shuffle/unshuffle
    if (shuffle) {
        shufflePlaylist(playlist);
    }
    else {
        unshufflePlaylist(playlist);
    }
    playlist->currentTrackPosition = 0; //First track
    playlist->currentTrackIndex = playlist->trackIndeces[playlist->currentTrackPosition]; //First track index
    //Check if should repeat
    if (loop) {
        repeatPlaylist(playlist);
    }
    else {
        norepeatPlaylist(playlist);
    }
    playMusic(playlist);
}

//Start playing next playlist song
void nextPlaylistSong(Playlist* playlist) {
    stopMusic(playlist); //Stop current song
    //If there are songs remaining in the playlist
    if (playlist->currentTrackPosition < playlist->trackCount - 1)
    { 
        //Next song
        playlist->currentTrackPosition++; 
        playlist->currentTrackIndex = playlist->trackIndeces[playlist->currentTrackPosition];
        playMusic(playlist);
    }
    //Else we stop playing music
    else {
        //If playlist is on repeat, then we go back to the beginning
        if (playlist->isRepeat) {
            playlist->currentTrackPosition = 0;
            playlist->currentTrackIndex = playlist->trackIndeces[playlist->currentTrackPosition];
            playMusic(playlist);
        }
    }
}

//Play the previous track
void prevPlaylistSong(Playlist* playlist) {
    //If there is a song before the current one
    if (playlist->currentTrackPosition > 0)
    {
        stopMusic(playlist);
        playlist->currentTrackPosition--; //Previous song
        playlist->currentTrackIndex = playlist->trackIndeces[playlist->currentTrackPosition];
        playMusic(playlist);
    }
    //Else we stop playing music
    else {
        stopMusic(playlist);
    }
}

//Shuffle
void shufflePlaylist(Playlist* playlist) {
    srand(time((time_t)NULL));

    //Fisher-Yates shuffle O(n)
    //The idea is that you start from the last element and swap one by one
    for (size_t i = playlist->trackCount - 1; i > 0; i--) {
        int j = rand() % (i + 1); //Random index from 0 to i
        swapIndeces(&playlist->trackIndeces[i], &playlist->trackIndeces[j]);
    }
    playlist->isShuffled = true;
}

//Unshuffle
void unshufflePlaylist(Playlist* playlist) {
    for (int i = 0; i < MAX_TRACKS; i++) {
        playlist->trackIndeces[i] = i;
    }
    playlist->isShuffled = false;
}

//Repeat playlist
void repeatPlaylist(Playlist* playlist) {
    playlist->isRepeat = true;
}
//Stop repeating playlist
void norepeatPlaylist(Playlist* playlist) {
    playlist->isRepeat = false;
}

//Plays current song from the beginning or returns to the previous song (simillar to the function on Spotify)
void playSongFromBeginningOrPrev(Playlist* playlist) {
    if (playlist->isPlaying) {
        //Current time is the time we get when the function is called
        Uint64 current_time = SDL_GetTicks64();
        //Delta is the difference between the time when we clicked the 
        //left arrow button and the time when the song begun
        Uint64 delta = current_time - playlist->startTime;
        //If the delta is more than 2 seconds
        if (delta > 2000) {
            stopMusic(playlist);
            Mix_PlayMusic(playlist->currentTrack->music, -1);//Restarts the current song
            playMusic(playlist);

        }
        //If the delta is less than 2 seconds
        else {
            prevPlaylistSong(playlist);//Plays the previous song
        }
    }

}

void increasePlaylistVolume(Playlist* playlist) {
    if (playlist->volume < 128) {
        playlist->volume++;
        Mix_VolumeMusic(playlist->volume);
    }
}

void decreasePlaylistVolume(Playlist* playlist) {
    if (playlist->volume > 0) {
        playlist->volume--;
        Mix_VolumeMusic(playlist->volume);
    }
}

//Frees allocated memory by the playlist
void clearPlaylist(Playlist* playlist) {
    Mix_FreeMusic(playlist->currentTrack->music);
    free(playlist->currentTrack);
    playlist->currentTrack->music = NULL;
    free(playlist);
}

void repeatSongOneTime(Playlist* playlist) {

    Mix_PlayMusic(playlist->currentTrack->music, 1);
};

void repeatSongInfinitely(Playlist* playlist) {
   
    Mix_PlayMusic(playlist->currentTrack->music, -1);
  
};