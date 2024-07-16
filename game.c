#include "maze.h"

bool initializeGame(Game* game) {
	    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		    printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		    return false;
	    }

	    game->window = SDL_CreateWindow("3D Maze Game",
			    SDL_WINDOWPOS_UNDEFINED,
			    SDL_WINDOWPOS_UNDEFINED,
			    SCREEN_WIDTH,
			    SCREEN_HEIGHT,
			    SDL_WINDOW_SHOWN);
	    if (game->window == NULL) {
		    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		    return false;
	    }

	    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);
	    if (game->renderer == NULL) {
		    printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		    return false;
	    }

	    game->player.x = SCREEN_WIDTH / 2;
	    game->player.y = SCREEN_HEIGHT / 2;
	    game->player.width = 1;
	    game->player.height = 1;
	    game->player.rotationAngle = PI / 4;
	    game->player.walkSpeed = 100;
	    game->player.turnSpeed = 45 * (PI / 180);

	    game->isRunning = true;

	    // Initialize map
	    initializeMap(game);

	    return true;
}

void shutdownGame(Game* game) {
	SDL_DestroyRenderer(game->renderer);
	SDL_DestroyWindow(game->window);
	SDL_Quit();
}

void renderGame(Game* game) {
	SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
	SDL_RenderClear(game->renderer);

	renderMap(game);
	renderPlayer(game);
	render3DProjection(game);

	SDL_RenderPresent(game->renderer);
}
