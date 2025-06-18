#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdio.h>
#include "game.h"
#include "render.h"
#include "api_client.h"
#include <time.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>

#define WINDOW_SIZE 600
#define CELL_COUNT    3
#define CELL_SIZE  (WINDOW_SIZE / CELL_COUNT)

#define TEAM1_NAME "Niebieski"
#define TEAM2_NAME "Czerwony"

static int score_blue = 0;
static int score_red  = 0;


void show_win_animation(SDL_Renderer *ren) {
    const int frame_count = 8;
    const char *frames[] = {
        "win3n.png",
        "win3n.png",
        "win3n.png",
        "frame_apngframe1.png",
        "frame_apngframe2.png",
        "frame_apngframe3.png",
        "frame_apngframe4.png",
        "frame_apngframe5.png",
    };

    SDL_Texture *textures[frame_count];

    for (int i = 0; i < frame_count; ++i) {
        SDL_Surface *surface = IMG_Load(frames[i]);
        if (!surface) {
            fprintf(stderr, "IMG_Load failed: %s\n", IMG_GetError());
            return;
        }
        textures[i] = SDL_CreateTextureFromSurface(ren, surface);
        SDL_FreeSurface(surface);
    }

    for (int i = 0; i < frame_count; ++i) {
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, textures[i], NULL, NULL);
        SDL_RenderPresent(ren);
        SDL_Delay(200);
    }

    for (int i = 0; i < frame_count; ++i) {
        SDL_DestroyTexture(textures[i]);
    }
}

void save_result_to_file(const char *winner) {
    FILE *file = fopen("wyniki.txt", "a");
    if (!file) {
        fprintf(stderr, "Nie można otworzyć pliku do zapisu wyników.\n");
        return;
    }

    time_t now = time(NULL);
    char *timestamp = ctime(&now);
    if (timestamp) {
        timestamp[strcspn(timestamp, "\n")] = 0;
    }

    fprintf(file, "[%s] Zwycięzca: %s | %s: %d, %s: %d\n",
        timestamp ? timestamp : "brak czasu",
        winner,
        TEAM1_NAME, score_blue,
        TEAM2_NAME, score_red
    );
    fclose(file);
}

int main(void) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "SDL_mixer initialization failed: %s\n", Mix_GetError());
        return 1;
    }
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init failed: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window   *win = SDL_CreateWindow(
        "Remisator 3000 - i tak nie wygrasz",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_SIZE, WINDOW_SIZE, 0
    );
    if (!win) {
        fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (!ren) {
        fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }

    init_board();
    int current = 1;
    bool running = true;
    Mix_Chunk *clickSound = Mix_LoadWAV("click.mp3");
    if (!clickSound) {
        fprintf(stderr, "Nie udało się załadować dźwięku: %s\n", Mix_GetError());
    }
    Mix_Music *bgMusic = Mix_LoadMUS("music.mp3");
    if (!bgMusic) {
        fprintf(stderr, "Nie udało się załadować muzyki: %s\n", Mix_GetError());
    } else {
        Mix_PlayMusic(bgMusic, -1);
    }
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                running = false;
            }

            else if (current == 1 && e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                int col = e.button.x / CELL_SIZE;
                int row = e.button.y / CELL_SIZE;
                if (make_move(row, col, current)) {
                    int res = check_win();
                    if (res == 1 || res == 2 || res == -1) {

                        if (res == 1) score_blue++;
                        else if (res == 2) score_red++;

                        char msg[128];
                        if (res == -1) {
                            snprintf(msg, sizeof msg,
                                "Remis!\n\nWynik:\n%s: %d\n%s: %d",
                                TEAM1_NAME, score_blue,
                                TEAM2_NAME, score_red
                            );
                        } else {
                            snprintf(msg, sizeof msg,
                                "%s wygrał!\n\nWynik:\n%s: %d\n%s: %d",
                                (res == 1 ? TEAM1_NAME : TEAM2_NAME),
                                TEAM1_NAME, score_blue,
                                TEAM2_NAME, score_red
                            );
                        }
                        SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Koniec gry", msg, win);
                        save_result_to_file(
                            res == -1 ? "Remis" :
                            (res == 1 ? TEAM1_NAME : TEAM2_NAME)
                        );
                        show_win_animation(ren);

                        init_board();
                        current = 1;
                    } else {
                        current = 2;
                    }
                }
            }
        }
        if (running && current == 2) {
            int ai_r, ai_c;
            if (get_best_move_api(2, board, &ai_r, &ai_c)) {
                make_move(ai_r, ai_c, 2);
                if (clickSound) Mix_PlayChannel(-1, clickSound, 0);
                int res = check_win();
                if (res == 1 || res == 2 || res == -1) {
                    if (res == 1) score_blue++;
                    else if (res == 2) score_red++;
                    char msg[128];
                    if (res == -1) {
                        snprintf(msg, sizeof msg,
                            "Remis!\n\nWynik:\n%s: %d\n%s: %d",
                            TEAM1_NAME, score_blue,
                            TEAM2_NAME, score_red
                        );
                    } else {
                        snprintf(msg, sizeof msg,
                            "%s wygrał!\n\nWynik:\n%s: %d\n%s: %d",
                            (res == 1 ? TEAM1_NAME : TEAM2_NAME),
                            TEAM1_NAME, score_blue,
                            TEAM2_NAME, score_red
                        );
                    }
                    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, "Koniec gry", msg, win);
                    show_win_animation(ren);
                    save_result_to_file(
                        res == -1 ? "Remis" :
                        (res == 1 ? TEAM1_NAME : TEAM2_NAME)
                    );

                    init_board();
                    current = 1;
                } else {
                    current = 1;
                }
            } else {
                current = 1;
            }
        }


        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
        SDL_RenderClear(ren);
        render_board(ren);
        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    Mix_FreeChunk(clickSound);
    SDL_Quit();
    return 0;
}

