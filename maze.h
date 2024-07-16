#ifndef MAZE_H
#define MAZE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include <stdbool.h>

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

// Initialization and shutdown
bool initializeGame(Game* game);
void shutdownGame(Game* game);

// Event handling
void handleInput(Game* game);

void updateGame(Game* game);

void renderGame(Game* game);
void renderMap(Game* game);
void renderPlayer(Game* game);

double normalizeAngle(double angle);
bool isInsideMap(double x, double y);
bool hasWallAt(Game* game, double x, double y);

#endif
