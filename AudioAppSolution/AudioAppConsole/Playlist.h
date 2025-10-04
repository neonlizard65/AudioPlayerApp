#include <SDL.h>
#include <SDL_mixer.h>

#define MAX_TRACKS 100 //Max number of tracks
#define MAX_PATH_LENGTH 256 //Max number of symbols in track path

//tracks - array of track paths
//currentTrackIndex - index of current track path in tracks array (-1 if playlist isn't started)
//currentTrack - track object (for memory freeing)
//isPlaying - is the playlist playing a song
//isRepeat - is the playlist repeating on end
//isShuffled - is the playlist randomly shuffled

typedef struct Playlist {
    char tracks[MAX_TRACKS][MAX_PATH_LENGTH];
    int currentTrackIndex;
    Mix_Music* currentTrack;
    int trackCount;
    bool isPlaying;
    bool isRepeat;
    bool isShuffled;
}Playlist;

//Creates a playlist from audio paths passed into the function in an array
//Requires track count to be passed to work with tracks array
//Returns pointer to created playlist (call clearPlaylist to free memory!) or NULL if the playlist fails to be created (Exceeds number of max tracks allowed or path length)
Playlist* createPlaylist(char** tracks, int trackCount);
//Frees allocated memory by the playlist
void clearPlaylist(Playlist* playlist);
//Start playing playlist
void startPlaylist(Playlist* playlist);
//Start playing next playlist song
void nextPlaylistSong(Playlist* playlist);
//Play the previous track
void prevPlaylistSong(Playlist* playlist);