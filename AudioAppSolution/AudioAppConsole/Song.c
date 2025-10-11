#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "Playlist.h"
#include "Song.h"
#include <Windows.h>

//"CEREMONY";
void createSong(Song* song) {
	Song song1;
	strcpy_s(song1.title, MAX_TITLE_LENGTH, "CEREMONY");
	strcpy_s(song1.artist, MAX_ARTIST_LENGTH, "Stray Kids");
	strcpy_s(song1.album, MAX_ALBUM_LENGTH, "KARMA");
}

