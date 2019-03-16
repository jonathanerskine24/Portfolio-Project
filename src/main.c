#include <stdio.h>
#include "../include/hash.h"
#include "../include/game2.h"



int main(int argc, char** argv[]) {

	int board_size = atoi(argv[1]);

	// if (board_size % 2 == 0) {
	// 	printf("Please select an odd number for board size\n");
	// 	return 0;
	// }


	const int FPS = 60;
	const int frameDelay = 1000/FPS;

	Uint32 frameStart;
	int frameTime;

	Game *game;

	game = (Game*)malloc(sizeof(Game));
	game->board_size = board_size;



	game->params.BOARD_WIDTH = 810;
	game->params.BOARD_HEIGHT = 810;
	// game->params.BOARD_WIDTH = 54 * board_size;
	// game->params.BOARD_HEIGHT = 54 * board_size;
	game->params.WINDOW_WIDTH = game->params.BOARD_WIDTH + 100;
	game->params.WINDOW_HEIGHT = game->params.BOARD_HEIGHT + 100;

	Init(game, "SCRABBLE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, game->params.BOARD_WIDTH, game->params.BOARD_HEIGHT + 100, false); // W then H
	Render(game);

	while (game->isRunning) {
		frameStart = SDL_GetTicks();

		HandleEvents(game);
		Update(game);
		Render(game);

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime) SDL_Delay(frameDelay-frameTime);
	}

	Clean(game);
	free(game);
	return 0;

}