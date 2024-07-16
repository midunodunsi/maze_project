#include "maze.h"

int main(int argc, char* argv[]) {
	Game game;

	if (!initializeGame(&game)) {
		printf("Failed to initialize game\n");
		return 1;
	}

	while (game.isRunning) {
	       	handleInput(&game);
		updateGame(&game);
		renderGame(&game);
		SDL_Delay(16);
	}

	shutdownGame(&game);
	    return 0;
}
