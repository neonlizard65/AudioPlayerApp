#ifndef SONG_H //Include guard 
#define SONG_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "Playlist.h"

#define MAX_TITLE_LENGTH 100 //Max number of symbols in the song title
#define MAX_ARTIST_LENGTH 100 //Max number of symbols in the song artist
#define MAX_ALBUM_LENGTH 100 //Max number of symbols in the song album


//title - stores a song title (string)
//artist - stores a song artist (string)
//album - stores a song album (string)
typedef struct Song {
	Mix_Music* music;
	char title[MAX_TITLE_LENGTH];
	char artist[MAX_ARTIST_LENGTH];
	char album[MAX_ALBUM_LENGTH];
	
}Song;

Song* createSong(char* title, char* artist, char* album);

void clearSong(Song* song);

void printSong(Song* song);

#endif /*SONG.H*/