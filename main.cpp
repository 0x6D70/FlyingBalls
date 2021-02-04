#include <iostream>

#define SDL_MAIN_HANDLED

#include <SDL2/SDL.h>
#include "game.h"

int main() {

    Game *game = new Game();
    game->init("Ball Physics Simulation", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, 0);

    while (game->running()) {
        game->handleEvents();
        game->update();
        game->render();
    }

    return 0;
}