#include <stdio.h>
// #include "../include/hash.h"
#include "../include/game2.h"



int main(int argc, char** argv[]) {



	// check to see if gamemode and board size were provided
	if (argc != 2) {
		printf("Please enter a game mode\n"); 
		return 1;
	}

	bool gamemode = 0;
	BOARD_SIZE = _BOARD_SIZE_;
	MAXIMUM_INDEX = BOARD_SIZE - 1;

	// set game mode
	if (strcmp(argv[1], "s") == 0) gamemode = SINGLEPLAYER;
	else if (strcmp(argv[1], "m") == 0) gamemode = MULTIPLAYER;
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

	if (BOARD_SIZE <= 17) game->gameinfo.params.TILE_SIZE = 54;
	else {
		game->gameinfo.params.TILE_SIZE = 980 / BOARD_SIZE;
	}

	game->gameinfo.board_size = BOARD_SIZE;
	game->ui.board.center = BOARD_SIZE / 2;
	game->gameinfo.gamemode = gamemode;
	CalculateParameters(game);

	// initialize game
	Init(game, "SCRABBLE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			game->gameinfo.params.WINDOW_WIDTH, game->gameinfo.params.WINDOW_HEIGHT, false);


	// run single player game
	if (game->gameinfo.gamemode == SINGLEPLAYER) {
		printf("Starting Singleplayer GAME!\n");
		while (game->gameinfo.isRunning) {

			frameStart = SDL_GetTicks();

			HandleSingleplayerEvents(game);
			Update_Singleplayer(game);
			Render(game);

			frameTime = SDL_GetTicks() - frameStart;

			if (frameDelay > frameTime) SDL_Delay(frameDelay-frameTime);
		}
		
	// run multiplayer game
	} else if (game->gameinfo.gamemode == MULTIPLAYER) {
		printf("Starting Multiplayer game!\n");
		while (game->gameinfo.isRunning) {
			frameStart = SDL_GetTicks();

			HandleMultiplayerEvents(game);
			Update_Multiplayer(game);
			RenderMP(game);

			frameTime = SDL_GetTicks() - frameStart;

			if (frameDelay > frameTime) SDL_Delay(frameDelay-frameTime);


		}
	}


	Clean(game);
	free(game);
	return 0;

}