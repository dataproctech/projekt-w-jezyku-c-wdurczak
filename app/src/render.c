#include "render.h"
#include "game.h"

#define WINDOW_SIZE 600
#define CELL_SIZE (WINDOW_SIZE / CELL_COUNT)

void draw_circle(SDL_Renderer *ren, int x, int y, int radius) {
    const int32_t diameter = (radius * 2);
    int32_t nx = (radius - 1);
    int32_t ny = 0;
    int32_t err = (nx - diameter);
    while (nx >= ny) {
        SDL_RenderDrawPoint(ren, x + nx, y + ny);
        SDL_RenderDrawPoint(ren, x + ny, y + nx);
        SDL_RenderDrawPoint(ren, x - ny, y + nx);
        SDL_RenderDrawPoint(ren, x - nx, y + ny);
        SDL_RenderDrawPoint(ren, x - nx, y - ny);
        SDL_RenderDrawPoint(ren, x - ny, y - nx);
        SDL_RenderDrawPoint(ren, x + ny, y - nx);
        SDL_RenderDrawPoint(ren, x + nx, y - ny);
        if (err <= 0) {
            ny++;
            err += ny * 2 + 1;
        } else {
            nx--;
            err -= nx * 2 + 1;
        }
    }
}

void render_board(SDL_Renderer *ren) {

    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    for (int i = 1; i < CELL_COUNT; ++i) {
        SDL_RenderDrawLine(ren, i * CELL_SIZE, 0, i * CELL_SIZE, WINDOW_SIZE);
        SDL_RenderDrawLine(ren, 0, i * CELL_SIZE, WINDOW_SIZE, i * CELL_SIZE);
    }
    for (int r = 0; r < CELL_COUNT; ++r) {
        for (int c = 0; c < CELL_COUNT; ++c) {
            int center_x = c * CELL_SIZE + CELL_SIZE / 2;
            int center_y = r * CELL_SIZE + CELL_SIZE / 2;
            int offset = CELL_SIZE / 3;

            if (board[r][c] == 1) {
                SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
                SDL_RenderDrawLine(ren, center_x - offset, center_y - offset,
                                   center_x + offset, center_y + offset);
                SDL_RenderDrawLine(ren, center_x - offset, center_y + offset,
                                   center_x + offset, center_y - offset);
            } else if (board[r][c] == 2) {
                SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
                draw_circle(ren, center_x, center_y, offset);
            }
        }
    }
}