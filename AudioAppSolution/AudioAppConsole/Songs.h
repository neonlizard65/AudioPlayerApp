#ifndef SONGS_H //Include guard 
#define SONGS_H
#include <SDL.h>
#include <SDL_mixer.h>
#include "Playlist.h"


#define MAX_TITLE_LENGTH 100 //Max number of symbols in the song title
#define MAX_ARTIST_LENGTH 100 //Max number of symbols in the song artist
#define MAX_ALBUM_LENGTH 100 //Max number of symbols in the song album

//title - stores a song title (string)
//artist - stores a song artist (string)
//album - stores a song album (string)
typedef struct Songs {
	Mix_Music* music;
	char title[MAX_TITLE_LENGTH];
	char artist[MAX_ARTIST_LENGTH];
	char album[MAX_ALBUM_LENGTH];
}Songs;

void createSongs(Songs* song);

#endif /*SONGS.H*/