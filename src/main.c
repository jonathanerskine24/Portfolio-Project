#include <stdio.h>
#include "../include/game2.h"


int main(void) {

	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 900;
	const int FPS = 60;
	const int frameDelay = 1000/FPS;

	Uint32 frameStart;
	int frameTime;

	Game *game;

	game = (Game*)malloc(sizeof(Game));

	Init(game, "SCRABBLE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, false); // W then H
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
