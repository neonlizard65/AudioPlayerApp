#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <string.h>
#include "Playlist.h"
#include <Windows.h>

//Creates playlist out of track paths
//Requires track count to be passed
//Returns pointer to created track (call clearPlaylist to free memory!) or NULL if the playlist fails to be created
Playlist* createPlaylist(char **tracks, int trackCount) {
    if (trackCount > MAX_TRACKS) {
        printf("Cannot create a playlist with more than 100 tracks");
        return NULL;
    }
    Playlist* playlist = (Playlist*)malloc(sizeof(Playlist));
    if (!playlist) {
        printf("Error while allocating memory for playlist");
        return NULL;
    }
    playlist->trackCount = trackCount;
    //Write into the tracks array
    for (size_t i = 0; i < trackCount; i++)
    {
        strcpy_s(playlist->tracks[i], MAX_PATH_LENGTH, tracks[i]);
    }
    return playlist;
}


//Start playing playlist
void startPlaylist(Playlist *playlist) {
    playlist->currentTrack = 0; //First track
    Mix_Music* track = Mix_LoadMUS(playlist->tracks[playlist->currentTrack]);
    Mix_PlayMusic(track, 0); 
    playlist->isPlaying = true;
}

//Start playing next playlist song
void nextPlaylistSong(Playlist* playlist) {
    //If there are songs remaining in the playlist
    if (playlist->currentTrack < playlist->trackCount)
    { 
        playlist->currentTrack++; //Next song
        Mix_Music* track = Mix_LoadMUS(playlist->tracks[playlist->currentTrack]);
        Mix_PlayMusic(track, 0);
        playlist->isPlaying = true;
    }
    //Else we stop playing music
    else {
        Mix_HaltMusic();
        playlist->isPlaying = false;
    }
}

//TODO:

//Previous track

//Shuffle

//Repeat

//Frees allocated memory by the playlist
void clearPlaylist(Playlist* playlist) {
    free(playlist);
}