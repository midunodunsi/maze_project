#include "maze.h"

void renderPlayer(Game* game) {
	    SDL_SetRenderDrawColor(game->renderer, 255, 0, 0, 255);
	    SDL_Rect playerRect = {
		    (int)(game->player.x - game->player.width / 2),
		    (int)(game->player.y - game->player.height / 2),
		    (int)game->player.width,
		    (int)game->player.height
	    };
	    SDL_RenderFillRect(game->renderer, &playerRect);
}

double normalizeAngle(double angle) {
	    angle = remainder(angle, TWO_PI);
	    if (angle < 0) {
		    angle += TWO_PI;
	    }
	    return angle;
}

bool hasWallAt(Game* game, double x, double y) {
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) {
		return true;
	}
	int mapGridIndexX = floor(x / TILE_SIZE);
	int mapGridIndexY = floor(y / TILE_SIZE);

	return game->map[mapGridIndexY][mapGridIndexX] != 0;
}


void movePlayer(Game* game, double newX, double newY) {
	if (!hasWallAt(game, newX, game->player.y)) {
		game->player.x = newX;
	} else {
		// Slide along the Y-axis
		if (!hasWallAt(game, game->player.x, newY)) {
    			game->player.y = newY;
		}
	}

	if (!hasWallAt(game, game->player.x, newY)) {
		game->player.y = newY;
	} else {
		// Slide along the X-axis
		if (!hasWallAt(game, newX, game->player.y)) {
			game->player.x = newX;
		}
	}
}
