#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "Song.h"
#include <Windows.h>


//returns -1 on error
//returns 0 on success
int createSong(Song* song, char* title, char* artist, char* album) {
    int titleLen = strlen(title);
    int artistLen = strlen(artist);
    int albumLen = strlen(album);

    //Check if track count passed is bigger, than the max allowed
    if (titleLen > MAX_TITLE_LENGTH) {
        printf("The title is too long");
        return -1;
    }
    if (artistLen > MAX_ARTIST_LENGTH) {
        printf("The artist name is too long");
        return -1;
    }
    if (albumLen > MAX_ALBUM_LENGTH) {
        printf("The album name is too long");
        return -1;
    }

    strcpy_s(song->title, MAX_TITLE_LENGTH, title);
    strcpy_s(song->artist, MAX_ARTIST_LENGTH, artist);
    strcpy_s(song->album, MAX_ALBUM_LENGTH, album);
    
    return 0;
}

void printSong(Song* song) {
    printf("Title: %s\nArtist: %s\nAlbum: %s\n", song->title, song->artist, song->album);
};

void clearSong(Song* song) {
    free(song);
}

