#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include <SDL2/SDL.h>

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

#define TEXTURE_WIDTH 64
#define TEXTURE_HEIGHT 64


extern int worldMap[mapWidth][mapHeight];
extern double posX, posY;
extern double dirX, dirY;
extern double planeX, planeY;
extern double time, oldTime;
extern double moveSpeed;
extern double rotSpeed;

#endif
