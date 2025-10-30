#ifndef LABEL_H //Include guard 
#define LABEL_H

#include <SDL2/SDL_ttf.h>
#include "Song.h"

void createText(SDL_Renderer* renderer, SDL_Rect messageRect, Song* song, int messageWidth, int messageHeight) {
    TTF_Font* font = TTF_OpenFont("./assets/font/timesnewromanpsmt.ttf", 24);
    SDL_Color white = { 255, 255, 255 };
    SDL_Surface* messageSurface = TTF_RenderText_Solid(font, song->title, white);
    SDL_Texture* messageTexture = SDL_CreateTextureFromSurface(renderer, messageSurface);
    SDL_FreeSurface(messageSurface);
    SDL_Rect messageRect;
    messageRect.x = 10;  //controls the rect's x coordinate
    messageRect.y = 10; // controls the rect's y coordinte
    messageRect.w = 400; // controls the width of the rect
    messageRect.h = 200;
    SDL_RenderCopy(renderer, messageTexture, NULL, &messageRect);
    SDL_RenderPresent(renderer);

}


#endif /*LABEL.H*/