#include "game.h"
#include <math.h>

SDL_Renderer *Game::renderer = NULL;
bool Game::isRunning = false;
SDL_Event Game::event;

void Game::init(const char *title, int xpos, int ypos, int width, int height, int flags) {

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "Subsystem Initialised!" << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window) {
            std::cout << "Window created" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Renderer created" << std::endl;
        }
        isRunning = true;
    } else {
        isRunning = false;
    }

    for (int i = 0; i < MAXBALLS; i++) {
        int x = rand() % WIDTH;
        int y = rand() % HEIGHT;

        int x_vel = rand() % (MAXVELOCITY -  MINVELOCITY + 1) + MINVELOCITY;
        int y_vel = rand() % (MAXVELOCITY -  MINVELOCITY + 1) + MINVELOCITY;
        int radius = rand() % (MAXRADIUS -  MINRADIUS + 1) + MINRADIUS;

        BallColor bcolor = (BallColor) (rand() % 4);

        balls.push_back(new Ball(x, y, bcolor, new Vector2D(x_vel, y_vel), radius));
    }
}

void Game::handleEvents() {
    SDL_PollEvent(&event);

    switch (event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
    }
}

void Game::checkBorderCollision(Ball *ball) {

    if (ball->y - ball->radius <= 0 && ball->velocity->y < 0) {
        ball->velocity->y *= -1;
    } else if (ball->y + ball->radius >= HEIGHT && ball->velocity->y > 0) {
        ball->velocity->y *= -1;
    } else if (ball->x - ball->radius <= 0 && ball->velocity->x < 0) {
        ball->velocity->x *= -1;
    } else if (ball->x + ball->radius >= WIDTH && ball->velocity->x > 0) {
        ball->velocity->x *= -1;
    }

}

int frames = 0;
int lastUpdate = 0;

void Game::updateFPS() {
    frames++;

    if (lastUpdate < SDL_GetTicks() / 1000) {
        // a seconds has past -> update FPS counter

        std::string title = "FPS: ";
        title += std::to_string(frames);

        SDL_SetWindowTitle(window, title.c_str());

        frames = 0;
        lastUpdate = SDL_GetTicks() / 1000;
    }
}

int lasttime = 0;

void Game::update() {
    updateFPS();
    checkBallCollision();

    int newtime = SDL_GetTicks();
    int diff = newtime - lasttime;

    if (diff > 10)
        diff = 10;

    for (Ball *ball : balls) {
        ball->x = ball->x + ball->velocity->x * (float) diff / 100;
        ball->y = ball->y + ball->velocity->y * (float) diff / 100;

        checkBorderCollision(ball);
    }

    lasttime = newtime;
}

// do all collision checks and update the velocity
void Game::checkBallCollision() {
    Ball **ballArr = &balls[0];
    int length = balls.size();

    for (int i = 0; i < length; i++) {
        for (int k = i + 1; k < length; k++) {
            Ball *ball1 = ballArr[i];
            Ball *ball2 = ballArr[k];

            float distance = std::hypot(ball1->x - ball2->x, ball1->y - ball2->y);

            if (distance <= ball1->radius + ball2->radius) {
                // ball1 and ball2 are colliding
                // update the velocity of both balls

                while (distance <= ball1->radius + ball2->radius) { // balls go back until they are not overlapping any more
                    ball1->x = ball1->x - ball1->velocity->x * (float) 1 / 100;
                    ball1->y = ball1->y - ball1->velocity->y * (float) 1 / 100;

                    ball2->x = ball2->x - ball2->velocity->x * (float) 1 / 100;
                    ball2->y = ball2->y - ball2->velocity->y * (float) 1 / 100;

                    distance = std::hypot(ball1->x - ball2->x, ball1->y - ball2->y);
                }

                float m1 = ball1->radius * ball1->radius * PI;
                float m2 = ball2->radius * ball2->radius * PI;

                Vector2D v1 = Vector2D(ball1->velocity->x, ball1->velocity->y);
                Vector2D v2 = Vector2D(ball2->velocity->x, ball2->velocity->y);

                // first ball
                Vector2D tmp1 = v1 - v2;
                Vector2D tmp2 = Vector2D(ball1->x - ball2->x, ball1->y - ball2->y);

                float dot = tmp1.x * tmp2.x + tmp1.y * tmp2.y;
                dot /= (distance * distance);

                float first = (2 * m2 / (m1 + m2));
                float second = dot;
                float third = (ball1->x - ball2->x);

                ball1->velocity->x -= (first * second * third);
                third = (ball1->y - ball2->y);
                ball1->velocity->y -= first * second * third;

                // second ball
                tmp1 = v2 - v1;
                tmp2 = Vector2D(ball2->x - ball1->x, ball2->y - ball1->y);

                dot = tmp1.x * tmp2.x + tmp1.y * tmp2.y;
                dot /= (distance * distance);

                ball2->velocity->x = v2.x - (2 * m1 / (m1 + m2)) * dot * (ball2->x - ball1->x);
                ball2->velocity->y = v2.y - (2 * m1 / (m1 + m2)) * dot * (ball2->y - ball1->y);
            }
        }
    }
}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // render everything
    for (Ball *ball : balls) {

        if (ball->color == RED) {
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        } else if (ball->color == YELLOW) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
        } else if (ball->color == GREEN) {
            SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
        } else if (ball->color == BLUE) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        }

        SDL_RenderFillCircle(Game::renderer, ball->x, ball->y, ball->radius);
    }

    SDL_RenderPresent(renderer);
}

int Game::SDL_RenderFillCircle(SDL_Renderer *renderer, int x, int y, int radius) {
    int offsetx, offsety, d;
    int status;

    offsetx = 0;
    offsety = radius;
    d = radius - 1;
    status = 0;

    while (offsety >= offsetx) {

        status += SDL_RenderDrawLine(renderer, x - offsety, y + offsetx, x + offsety, y + offsetx);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y + offsety, x + offsetx, y + offsety);
        status += SDL_RenderDrawLine(renderer, x - offsetx, y - offsety, x + offsetx, y - offsety);
        status += SDL_RenderDrawLine(renderer, x - offsety, y - offsetx, x + offsety, y - offsetx);

        if (status < 0) {
            status = -1;
            break;
        }

        if (d >= 2 * offsetx) {
            d -= 2 * offsetx + 1;
            offsetx += 1;
        } else if (d < 2 * (radius - offsety)) {
            d += 2 * offsety - 1;
            offsety -= 1;
        } else {
            d += 2 * (offsety - offsetx - 1);
            offsety -= 1;
            offsetx += 1;
        }
    }

    return status;
}