#ifndef _CONSTANTS_H
#define _CONSTANTS_H

#include <SDL2/SDL.h>

#define mapWidth 24
#define mapHeight 24
#define TILE_WIDTH 64
#define TILE_HEIGHT 64

#define screenWidth 640
#define screenHeight 480

#define TEXTURE_WIDTH 64
#define TEXTURE_HEIGHT 64

#define MAP_WIDTH mapWidth
#define MAP_HEIGHT mapHeight

extern int worldMap[mapWidth][mapHeight];
extern double posX, posY;
extern double dirX, dirY;
extern double planeX, planeY;
extern double time, oldTime;
extern double moveSpeed;
extern double rotSpeed;
extern int lifeCount;

#endif
