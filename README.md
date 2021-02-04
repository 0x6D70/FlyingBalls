# FlyingBalls

FlyingBalls shows balls flying around in a space without gravity with physically correct collisions.

## Building

### Windows

Make sure that you have g++ installed and run the following command:
```
g++ -I ./include/ -o bin/FlyingBalls ball.cpp game.cpp main.cpp Vector2D.cpp -std=c++11 -lstdc++ -lSDL2main -lSDL2
```
The Flyingballs.exe can be found in the ``bin`` directory.

### Linux

Make sure to install SDL2. Then run:
```
Comming soon
```

## Making Changes

In the ``game.h`` you can change a few variables.
 * MAXBALLS - number of balls
 * MAXRADIUS - maximum radius of ball
 * MINRADIUS - minimum radius of ball
 * MAXVELOCITY - maximium velocity of ball
 * MINVELOCITY - minimum velocity of ball
 * WIDTH - width of the window
 * HEIGHT - height of the window
