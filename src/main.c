#include <stdio.h>
// #include "../include/hash.h"
#include "../include/game2.h"


int main(int argc, char** argv[]) {

	// check to see if gamemode and board size were provided
	if (argc != 3) {
		printf("Please enter a board size and game mode\n"); 
		return 1;
	}

	int gamemode = 0;
	BOARD_SIZE = atoi(argv[1]);
	MAXIMUM_INDEX = BOARD_SIZE - 1;

	// set game mode
	if (strcmp(argv[2], "s") == 0) gamemode = 1;
	else if (strcmp(argv[2], "m" == 0)) gamemode = 2;
	else {
		printf("Please enter m for multiplayer or s for singleplayer vs computer\n");
		return 1;
	}

	// board size must be odd, if not odd reject and tell user to enter odd number
	if (BOARD_SIZE % 2 == 0) {
		printf("Please select an odd number for board size\n");
		return 1;
	}

	const int FPS = 100;
	const int frameDelay = 1000/FPS;

	Uint32 frameStart;
	int frameTime;

	// game declaration and malloc
	Game *game;
	game = (Game*)malloc(sizeof(Game));


	game->gameinfo.board_size = BOARD_SIZE;
	game->ui.board.center = BOARD_SIZE / 2;
	game->gameinfo.gamemode = gamemode;

	game->gameinfo.params.BOARD_WIDTH = 810;
	game->gameinfo.params.BOARD_HEIGHT = 810;
	// game->params.BOARD_WIDTH = 54 * board_size;
	// game->params.BOARD_HEIGHT = 54 * board_size;
	game->gameinfo.params.WINDOW_WIDTH = game->gameinfo.params.BOARD_WIDTH + 100;
	game->gameinfo.params.WINDOW_HEIGHT = game->gameinfo.params.BOARD_HEIGHT + 100;

	// initialize the game (open the window, create renderer, etc)
	// InitMenuWindow(game, "SCRABBLE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
	// 		game->gameinfo.params.BOARD_WIDTH, game->gameinfo.params.BOARD_HEIGHT + 100, false); // W then H
	
	// RenderMenu(game);

	// while (game->gameinfo.gamemode == NONE) {
	// 	frameStart = SDL_GetTicks();

	// 	HandleMainMenuEvents(game);
	// 	RenderMenu(game);

	// 	frameTime = SDL_GetTicks() - frameStart;

	// 	if (frameDelay > frameTime) SDL_Delay(frameDelay-frameTime);
	// }

	// initialize game
	Init(game, "SCRABBLE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			game->gameinfo.params.BOARD_WIDTH, game->gameinfo.params.BOARD_HEIGHT + 100, false);


	while (game->gameinfo.isRunning) {

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