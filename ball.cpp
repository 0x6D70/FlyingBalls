#include "ball.h"

Ball::Ball(float x, float y, BallColor color, Vector2D *velocity, int radius) {
    this->x = x;
    this->y = y;
    this->color = color;
    this->velocity = velocity;
    this->radius = radius;
}

std::ostream& operator<<(std::ostream &strm, const Ball &ball) {
    strm << "[";
    strm << "x=" << ball.x;
    strm << " y=" << ball.y;
    strm << " velocity=" << ball.velocity;
    strm << "]";
    return strm;
}