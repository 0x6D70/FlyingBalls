#ifndef SDL2_GLEW_OPENGL_TEMPLATE_GAME_H
#define SDL2_GLEW_OPENGL_TEMPLATE_GAME_H

#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <vector>
#include "ball.h"
#include "Vector2D.h"
#include <cmath>

#define MAXBALLS 100
#define MAXRADIUS 20
#define MINRADIUS 2
#define MAXVELOCITY 20
#define MINVELOCITY 2
#define WIDTH 1200
#define HEIGHT 800

class Game {
public:
    Game() {}

    ~Game() {}

    void init(const char *title, int xpos, int ypos, int width, int height, int flags);

    void handleEvents();

    void update();

    void render();

    bool running() { return isRunning; };

    void updateFPS();

    static SDL_Renderer *renderer;
    static SDL_Event event;
    static bool isRunning;

    const float PI = std::atan(1) * 4;

private:
    int SDL_RenderFillCircle(SDL_Renderer *renderer, int x, int y, int radius);

    void checkBorderCollision(Ball *ball);

    void checkBallCollision();

    SDL_Window *window;
    std::vector<Ball *> balls;
};

#endif
