#include "maze.h"

void handleInput(Game* game) {
	    SDL_Event event;
	    while (SDL_PollEvent(&event) != 0) {
		    if (event.type == SDL_QUIT) {
			    game->isRunning = false;
		    }

		    if (event.type == SDL_KEYDOWN) {
			    switch (event.key.keysym.sym) {
				    case SDLK_ESCAPE:
					    game->isRunning = false;
					    break;
				    case SDLK_RIGHT:
					    game->player.rotationAngle += game->player.turnSpeed;
					    game->player.rotationAngle = normalizeAngle(game->player.rotationAngle);
					    break;
				    case SDLK_LEFT:
					    game->player.rotationAngle -= game->player.turnSpeed;
					    game->player.rotationAngle = normalizeAngle(game->player.rotationAngle);
					    break;

				    case SDLK_w: {
							 double moveStep = game->player.walkSpeed * 0.1;
							 double newX = game->player.x + cos(game->player.rotationAngle) * moveStep;
							 double newY = game->player.y + sin(game->player.rotationAngle) * moveStep;
							 movePlayer(game, newX, newY);
							 break;
	     					 }
	
				    case SDLK_s: {
							 double moveStep = game->player.walkSpeed * 0.1;
							 double newX = game->player.x - cos(game->player.rotationAngle) * moveStep;
							 double newY = game->player.y - sin(game->player.rotationAngle) * moveStep;
							 movePlayer(game, newX, newY);
							 break;
						 }

				    case SDLK_d: {

							 double moveStep = game->player.walkSpeed * 0.1;
							 double newX = game->player.x + cos(game->player.rotationAngle + PI / 2) * moveStep;
							 double newY = game->player.y + sin(game->player.rotationAngle + PI / 2) * moveStep;
							 movePlayer(game, newX, newY);
							 break;
						 }

				    case SDLK_a: {
							 double moveStep = game->player.walkSpeed * 0.1;
							 double newX = game->player.x + cos(game->player.rotationAngle - PI / 2) * moveStep;
							 double newY = game->player.y + sin(game->player.rotationAngle - PI / 2) * moveStep;
							 movePlayer(game, newX, newY);
							 break;
						 }
			    }
		    }
	    }
}
