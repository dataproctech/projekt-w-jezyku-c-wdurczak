//
// Created by Wojciech Durczak on 26/04/2025.
//
#include "game.h"
#include "gui.h"

int main(int argc, char *argv[]) {
    Game game;
    //game_init(&game);
    gui_start(&game, argc, argv);
    return 0;
}