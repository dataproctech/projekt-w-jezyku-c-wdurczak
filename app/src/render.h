#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>

void render_board(SDL_Renderer *ren);
void draw_circle(SDL_Renderer *ren, int x, int y, int radius);

#endif