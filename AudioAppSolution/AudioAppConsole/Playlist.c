#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <string.h>
#include "Playlist.h"
#include <Windows.h>

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
    playlist->currentTrack = NULL;
    playlist->currentTrackIndex = -1;
    playlist->trackCount = trackCount;
    playlist->isRepeat = false;
    playlist->isShuffled = false;
    //Write into the tracks array
    for (size_t i = 0; i < trackCount; i++)
    {
        strcpy_s(playlist->tracks[i], MAX_PATH_LENGTH, tracks[i]);
    }
    return playlist;
}


//Start playing playlist
void startPlaylist(Playlist *playlist) {
    //Free up any music that may be currently playing
    if (playlist->currentTrack) {
        Mix_FreeMusic(playlist->currentTrack);
        playlist->currentTrack = NULL;
    }
    playlist->currentTrackIndex = 0; //First track
    playlist->currentTrack = Mix_LoadMUS(playlist->tracks[playlist->currentTrackIndex]);
    Mix_PlayMusic(playlist->currentTrack, 0);
    playlist->isPlaying = true;
}

//Start playing next playlist song
void nextPlaylistSong(Playlist* playlist) {
    //If there are songs remaining in the playlist
    if (playlist->currentTrackIndex < playlist->trackCount)
    { 
        if (playlist->currentTrack) {
            Mix_FreeMusic(playlist->currentTrack);
            playlist->currentTrack = NULL;
        }
        playlist->currentTrackIndex++; //Next song
        playlist->currentTrack = Mix_LoadMUS(playlist->tracks[playlist->currentTrackIndex]);
        Mix_PlayMusic(playlist->currentTrack, 0);
        playlist->isPlaying = true;
    }
    //Else we stop playing music
    else {
        playlist->isPlaying = false;
        Mix_HaltMusic();
        if (playlist->currentTrack) {
            Mix_FreeMusic(playlist->currentTrack);
            playlist->currentTrack = NULL;
        }
    }
}

//Play the previous track
void prevPlaylistSong(Playlist* playlist) {
    //If there is a song before the current one
    if (playlist->currentTrackIndex >= 0)
    {
        if (playlist->currentTrack) {
            Mix_FreeMusic(playlist->currentTrack);
            playlist->currentTrack = NULL;
        }
        playlist->currentTrackIndex--; //Previous song
        playlist->currentTrack = Mix_LoadMUS(playlist->tracks[playlist->currentTrackIndex]);
        Mix_PlayMusic(playlist->currentTrack, 0);
        playlist->isPlaying = true;
    }
    //Else we stop playing music
    else {
        playlist->isPlaying = false; 
        Mix_HaltMusic();
        if (playlist->currentTrack) {
            Mix_FreeMusic(playlist->currentTrack);
            playlist->currentTrack = NULL;
        }
    }
}

//TODO:
//Shuffle

//Repeat

//Frees allocated memory by the playlist
void clearPlaylist(Playlist* playlist) {
    free(playlist);
}