#include <stdio.h>
#include "../include/game2.h"



int main(void) {


	const int FPS = 60;
	const int frameDelay = 1000/FPS;

	Uint32 frameStart;
	int frameTime;

	Game *game;

	game = (Game*)malloc(sizeof(Game));

	game->params.BOARD_WIDTH = 810;
	game->params.BOARD_HEIGHT = 810;
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