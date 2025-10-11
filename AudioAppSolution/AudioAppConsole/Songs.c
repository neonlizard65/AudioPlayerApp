#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include <string.h>
#include "Playlist.h"
#include "Songs.h"
#include <Windows.h>
#include <SDL_ttf.h>

//"CEREMONY";
void createSongs(Songs* song) {
	Songs song1;
	strcpy_s(song1.title, MAX_TITLE_LENGTH, "CEREMONY");
	strcpy_s(song1.artist, MAX_ARTIST_LENGTH, "Stray Kids");
	strcpy_s(song1.album, MAX_ALBUM_LENGTH, "KARMA");
}

