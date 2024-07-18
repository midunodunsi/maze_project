#include "maze.h"

bool isInsideMap(double x, double y) {
	return x >= 0 && x <= MAP_NUM_COLS * TILE_SIZE && y >= 0 && y <= MAP_NUM_ROWS * TILE_SIZE;
}
void castAllRays(Game* game) {
	int numRays = NUM_RAYS;
	double rayAngle = game->player.rotationAngle - (FOV / 2);

	for (int i = 0; i < numRays; i++) {
		double xIntercept, yIntercept;
		double xStep, yStep;

		bool foundHorzWallHit = false;
		double horzWallHitX = 0;
		double horzWallHitY = 0;
		double horzWallDist = __DBL_MAX__;
		bool horzWallIsVertical = false;

	
		bool foundVertWallHit = false;
		double vertWallHitX = 0;
		double vertWallHitY = 0;
		double vertWallDist = __DBL_MAX__;
		bool vertWallIsVertical = false;

		// Horizontal ray-grid intersection
		bool isRayFacingDown = rayAngle > 0 && rayAngle < PI;
		bool isRayFacingUp = !isRayFacingDown;

		bool isRayFacingRight = rayAngle < 0.5 * PI || rayAngle > 1.5 * PI;
		bool isRayFacingLeft = !isRayFacingRight;

		// Find the y-coordinate of the closest horizontal grid intersection
		yIntercept = floor(game->player.y / TILE_SIZE) * TILE_SIZE;
		yIntercept += isRayFacingDown ? TILE_SIZE : 0;

		// Find the x-coordinate of the closest horizontal grid intersection
		xIntercept = game->player.x + (yIntercept - game->player.y) / tan(rayAngle);

	    	// Calculate the increment xStep and yStep
		yStep = TILE_SIZE;
		yStep *= isRayFacingUp ? -1 : 1;

		xStep = TILE_SIZE / tan(rayAngle);
		xStep *= (isRayFacingLeft && xStep > 0) ? -1 : 1;
		xStep *= (isRayFacingRight && xStep < 0) ? -1 : 1;

		double nextHorzTouchX = xIntercept;
		double nextHorzTouchY = yIntercept;

		// Increment xStep and yStep until we find a wall

		while (isInsideMap(nextHorzTouchX, nextHorzTouchY)) {
	    		double xToCheck = nextHorzTouchX;
    			double yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);

			if (hasWallAt(game, xToCheck, yToCheck)) {
				foundHorzWallHit = true;
				horzWallHitX = nextHorzTouchX;
				horzWallHitY = nextHorzTouchY;
				horzWallDist = distanceBetweenPoints(game->player.x, game->player.y, horzWallHitX, horzWallHitY);
				horzWallIsVertical = false;
				break;
			} else {
				nextHorzTouchX += xStep;
				nextHorzTouchY += yStep;
			}
		}

		// Vertical ray-grid intersection
		xIntercept = floor(game->player.x / TILE_SIZE) * TILE_SIZE;
	    	xIntercept += isRayFacingRight ? TILE_SIZE : 0;

    		yIntercept = game->player.y + (xIntercept - game->player.x) * tan(rayAngle);

		xStep = TILE_SIZE;
		xStep *= isRayFacingLeft ? -1 : 1;

		yStep = TILE_SIZE * tan(rayAngle);
		yStep *= (isRayFacingUp && yStep > 0) ? -1 : 1;
		yStep *= (isRayFacingDown && yStep < 0) ? -1 : 1;

		double nextVertTouchX = xIntercept;
		double nextVertTouchY = yIntercept;

		while (isInsideMap(nextVertTouchX, nextVertTouchY)) {
			double xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
			double yToCheck = nextVertTouchY;

			if (hasWallAt(game, xToCheck, yToCheck)) {
				foundVertWallHit = true;
				vertWallHitX = nextVertTouchX;
				vertWallHitY = nextVertTouchY;
				vertWallDist = distanceBetweenPoints(game->player.x, game->player.y, vertWallHitX, vertWallHitY);
				vertWallIsVertical = true;
				break;
			} else {
				nextVertTouchX += xStep;
				nextVertTouchY += yStep;
			}
		}

		double wallHitX, wallHitY;
		double distance;
		bool isVertical;

		if (vertWallDist < horzWallDist) {
			wallHitX = vertWallHitX;
			wallHitY = vertWallHitY;
			distance = vertWallDist;
			isVertical = vertWallIsVertical;
		} else {
			wallHitX = horzWallHitX;
			wallHitY = horzWallHitY;
			distance = horzWallDist;
			isVertical = horzWallIsVertical;
		}

		Ray ray = {distance, isVertical};
		renderWallSlice(game, ray, i);

		rayAngle += FOV / NUM_RAYS;
	}
}

void renderWallSlice(Game* game, Ray ray, int stripId) {
	double distanceProjPlane = (SCREEN_WIDTH / 2) / tan(FOV / 2);
	double wallHeight = (TILE_SIZE / ray.distance) * distanceProjPlane;

	int wallTopPixel = (SCREEN_HEIGHT / 2) - (wallHeight / 2);
	wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

	int wallBottomPixel = (SCREEN_HEIGHT / 2) + (wallHeight / 2);
	wallBottomPixel = wallBottomPixel > SCREEN_HEIGHT ? SCREEN_HEIGHT : wallBottomPixel;

	SDL_SetRenderDrawColor(game->renderer, ray.isVertical ? 255 : 0, ray.isVertical ? 0 : 255, 0, 255);
	SDL_RenderDrawLine(game->renderer, stripId, wallTopPixel, stripId, wallBottomPixel);
}

void render3DProjection(Game* game) {
	castAllRays(game);
}
