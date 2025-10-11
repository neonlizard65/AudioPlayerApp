#ifndef PLAYLIST_H //Include guard 
#define PLAYLIST_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include "Song.h"

#define MAX_TRACKS 100 //Max number of tracks
#define MAX_PATH_LENGTH 256 //Max number of symbols in track path
#define DOUBLE_PRESS_TIME 500 // In milliseconds, for playing songs from beginning

//tracks - array of track paths
//currentTrackIndex - index of current track path in tracks array (-1 if playlist isn't started)
//currentTrack - track object (for memory freeing)
//isPlaying - is the playlist playing a song
//isRepeat - is the playlist repeating on end
//isShuffled - is the playlist randomly shuffled
//startTime - counts the time since the song started
//volume - defines the volume of the playlist (0 - 128)
typedef struct Playlist {
    char tracks[MAX_TRACKS][MAX_PATH_LENGTH];
    int currentTrackIndex;
    Song* currentTrack;
    int trackCount;
    bool isPlaying;
    bool isRepeat;
    bool isShuffled;
    Uint32 startTime;
    int volume;
}Playlist;

//Creates a playlist from audio paths passed into the function in an array
//Requires track count to be passed to work with tracks array
//Returns pointer to created playlist (call clearPlaylist to free memory!) or NULL if the playlist fails to be created (Exceeds number of max tracks allowed or path length)
Playlist* createPlaylist(char** tracks, int trackCount);
//Frees allocated memory by the playlist
void clearPlaylist(Playlist* playlist);
//Start playing playlist. Indicate if should be looped or not
void startPlaylist(Playlist* playlist, bool loop);
//Start playing next playlist song
void nextPlaylistSong(Playlist* playlist);
//Play the previous track
void prevPlaylistSong(Playlist* playlist);
//Repeat the playlist
void repeatPlaylist(Playlist* playlist);
//Stop repeating playlist
void norepeatPlaylist(Playlist* playlist);
//Play song again
void playSongFromBeginningOrPrev(Playlist* playlist);
//Increases the song's volume
void increasePlaylistVolume(Playlist* playlist);
//Decreases the song's volume
void decreasePlaylistVolume(Playlist* playlist);
#endif /*PLAYLIST.H*/
