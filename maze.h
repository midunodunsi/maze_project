#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Constants */

#define PI 3.14159265
#define TWO_PI 6.28318530

#define TILE_SIZE 64
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define MAP_WIDTH 24
#define MAP_HEIGHT 24
#define FOV (60 * (PI / 180))
#define NUM_RAYS SCREEN_WIDTH
#define MAP_NUM_ROWS 13
#define MAP_NUM_COLS 20

/* Data Structures */

// Structure to hold the player's state
typedef struct {
	double x, y;
	double width,height;
	double rotationAngle;
	double walkSpeed;
	double turnSpeed;
} Player;

// Structure to hold the game's state
typedef struct {
	SDL_Window* window;
	SDL_Renderer* renderer;
	Player player;
	bool isRunning;
	int map[MAP_NUM_ROWS][MAP_NUM_COLS];
} Game;

typedef struct {
	    double distance;
	        bool isVertical;
} Ray;

/* function Declarations */

// game.c
bool initializeGame(Game* game);
void shutdownGame(Game* game);
void updateGame(Game* game);
void cleanUp(Game* game);
void renderGame(Game* game);

// input.c
void handleInput(Game* game);
void processInput(Game* game);

// player.c
void renderPlayer(Game* game);
void movePlayer(Game* game, double newX, double newY);
bool hasWallAt(Game* game, double x, double y);
double normalizeAngle(double angle);
double distanceBetweenPoints(double x1, double y1, double x2, double y2);double normalizeAngle(double angle);

// map.c
void initializeMap(Game* game);
void renderMap(Game* game);
void loadMapFromFile(Game* game, const char* filename);

// raycasting.c
void castAllRays(Game* game);
void renderWallSlice(Game* game, Ray ray, int stripId);
void render3DProjection(Game* game);
void renderRays(Game* game, Ray rays[]);
double castRay(Game* game, double rayAngle, bool *isVerticalHit);

#endif
