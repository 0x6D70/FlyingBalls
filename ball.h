#ifndef FLYINGBALLSPHYSICS_BALL_H
#define FLYINGBALLSPHYSICS_BALL_H

#include "Vector2D.h"

enum BallColor {
    RED, BLUE, GREEN, YELLOW
};

class Ball {
public:
    Ball(float x, float y, BallColor color, Vector2D *velocity, int radius = 15);
    friend std::ostream& operator<<(std::ostream &strm, const Ball &ball);

    float x;
    float y;
    int radius;
    BallColor color;

    Vector2D *velocity;
};

#endif //FLYINGBALLSPHYSICS_BALL_H
