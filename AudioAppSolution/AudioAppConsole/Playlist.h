#include <SDL.h>
#include <SDL_mixer.h>

#define MAX_TRACKS 100 //Max number of tracks
#define MAX_PATH_LENGTH 256 //Max number of symbols in track path

//tracks - array of track paths
//currentTrack - index of current track path in tracks array
//isPlaying - is the playlist playing a song
//isRepeat - is the playlist repeating on end
//isShuffle - is the playlist randomly shuffled

typedef struct Playlist {
    char tracks[MAX_TRACKS][MAX_PATH_LENGTH];
    int currentTrack;
    int trackCount;
    bool isPlaying;
    bool isRepeat;
    bool isShuffle;
}Playlist;

//Creates playlist out of track paths
//Requires track count to be passed
//Returns pointer to created track (call clearPlaylist to free memory!) or NULL if the playlist fails to be created
Playlist* createPlaylist(char** tracks, int trackCount);
//Frees allocated memory by the playlist
void clearPlaylist(Playlist* playlist);
//Start playing playlist
void startPlaylist(Playlist* playlist);
//Start playing next playlist song
void nextPlaylistSong(Playlist* playlist);