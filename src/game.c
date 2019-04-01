#include <stdlib.h>
#include <time.h>
#include "../include/game2.h"
#include "../include/game_initialization.h"
#include "../include/types.h"
#include "../include/helper.h"
#include "../include/tileplacement.h"
#include "../include/computer.h"

int numcount = 0;

SDL_Texture* LoadTexture(const char* texture, SDL_Renderer* ren) {
        SDL_Surface *tempSurface = IMG_Load(texture);
        SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, tempSurface);
        SDL_FreeSurface(tempSurface);
        return tex;
}



void Init(Game* game, const char* title, int xpos, int ypos, int width, int height, bool fullScreen) {

	SDL_DestroyRenderer(game->renderer);
	SDL_DestroyWindow(game->window);

	srand(time(NULL));

	int flags = 0;
	const int BOARD_WIDTH = 800;
	const int BOARD_HEIGHT = 800;

	if (fullScreen) flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		printf("Subsystems initialized...\n");
		game->window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (game->window) { // confirm window was created
			printf("Window created!\n");
		}

		game->renderer = SDL_CreateRenderer(game->window, -1, 0);

		if (game->renderer) { // confirm renderer was created
			SDL_SetRenderDrawColor(game->renderer, 27, 27, 27, 255);
			printf("Renderer created!\n");
		}

		InitializeGame(game);

	} else {
		game->gameinfo.isRunning = false;
	}
}

// finish this

void InitMenuWindow(Game* game, const char* title, int xpos, int ypos, int width, int height, bool fullScreen) {

	srand(time(NULL));

	int flags = 0;
	const int BOARD_WIDTH = 800;
	const int BOARD_HEIGHT = 800;

	if (fullScreen) flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {

		printf("Subsystems initialized...\n");
		game->window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (game->window) { // confirm window was created
			printf("Window created!\n");
		}

		game->renderer = SDL_CreateRenderer(game->window, -1, 0);

		if (game->renderer) { // confirm renderer was created
			SDL_SetRenderDrawColor(game->renderer, 27, 27, 27, 255);
			printf("Renderer created!\n");
		}

		InitializeMenu(game);

	} else {
		game->gameinfo.isRunning = false;
	}
}


void HandleSingleplayerEvents(Game* game) {

	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_QUIT:
			game->gameinfo.isRunning = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				case SDLK_RETURN:
					printf("enter\n");
					PrintBoard(&game->ui.board);
					break;
			}
		case SDL_MOUSEBUTTONDOWN:


			// left click
			if (event.button.button == SDL_BUTTON_LEFT) {

				// get mouse position
				Position mousepos = GetMousePos(event);

				// check if clicked tile in hand
				if (mousepos.y > 810) {
					if (mousepos.x < 700) {
						int index = mousepos.x / 100;
						if (game->ui.tilebar.playerTiles[index].placed == false) {
							game->ui.tilebar.highlightedRectIndex = index;
							game->gameinfo.tileSelected = true;
							game->gameinfo.selectedTile = game->ui.tilebar.playerTiles[game->ui.tilebar.highlightedRectIndex].val;
						}

					}  else if (CheckClick(mousepos, game->ui.tilebar.submitButtonRect)) {
						// printf("Submit\n");
						if (game->ui.board.numStagedTiles == 0) break;
						if (SubmitWord(&game->ui, &game->gameinfo.player1score)) {
							game->gameinfo.player1consecutivePasses = 0;
							RefillTiles(&game->ui.tilebar);
							PrintScore(game);
							game->gameinfo.turn = AI;
							printf("Turn : %d\n", game->gameinfo.turn);
						} else RejectMove(&game->ui, &game->ui.tilebar);
					} else if (CheckClick(mousepos, game->ui.tilebar.swapButtonRect)) {
						game->gameinfo.player1consecutivePasses++;
						SwapTiles(&game->ui.tilebar);
						game->gameinfo.turn = AI;
					}

				} else {
					// game->ui.tilebar.highlightedRectIndex = -1;
					// game->gameinfo.tileSelected = false;
				}

				// check if selected board tile
				if ((game->gameinfo.tileSelected) && (mousepos.y < 810)) {
					// printf("!\n");
					SelectBoardTile(game, mousepos);
					PlaceTile(&game->gameinfo, &game->ui.board);
					game->gameinfo.tileSelected = false;
					game->ui.tilebar.playerTiles[game->ui.tilebar.highlightedRectIndex].placed = true;
					game->ui.tilebar.highlightedRectIndex = -1;
				}



			// right click
			} else if (event.button.button == SDL_BUTTON_RIGHT) {
				//
			}

		default:
			break;
	}
}

void HandleMultiplayerEvents(Game *game) {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_QUIT:
			game->gameinfo.isRunning = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				case SDLK_RETURN:
					printf("enter\n");
					PrintBoard(&game->ui.board);
					break;
			}
		case SDL_MOUSEBUTTONDOWN:


			// left click
			if (event.button.button == SDL_BUTTON_LEFT) {

				// get mouse position
				Position mousepos = GetMousePos(event);

				// check if clicked tile in hand
				if (mousepos.y > 810) {
					if (mousepos.x < 700) {
						if (game->gameinfo.turn == PLAYER_ONE) {

							int index = mousepos.x / 100;
							if (game->ui.tilebar.playerTiles[index].placed == false) {
								game->ui.tilebar.highlightedRectIndex = index;
								game->gameinfo.tileSelected = true;
								game->gameinfo.selectedTile = game->ui.tilebar.playerTiles[game->ui.tilebar.highlightedRectIndex].val;
							}
						} else {
							int index = mousepos.x / 100;
							if (game->ui.player2orAI.playerTiles[index].placed == false) {
								game->ui.player2orAI.highlightedRectIndex = index;
								game->gameinfo.tileSelected = true;
								game->gameinfo.selectedTile = game->ui.player2orAI.playerTiles[game->ui.player2orAI.highlightedRectIndex].val;
							}
						}


					}  else if (CheckClick(mousepos, game->ui.tilebar.submitButtonRect)) {
						if (game->ui.board.numStagedTiles == 0) break;

						if (game->gameinfo.turn == PLAYER_ONE) {
							if (SubmitWord(&game->ui, &game->gameinfo.player1score)) {
								game->gameinfo.player1consecutivePasses = 0;
								RefillTiles(&game->ui.tilebar);
								PrintScore(game);
								game->gameinfo.turn = PLAYER_TWO;
							} else RejectMove(&game->ui, &game->ui.tilebar);
						} 
						else {
							if (SubmitWord(&game->ui, &game->gameinfo.player2score)) {
								game->gameinfo.player2consecutivePasses = 0;
								RefillTiles(&game->ui.player2orAI);
								PrintScore(game);
								game->gameinfo.turn = PLAYER_ONE;
							} else RejectMove(&game->ui, &game->ui.player2orAI);
						}


					} else if (CheckClick(mousepos, game->ui.tilebar.swapButtonRect)) {

						if (game->gameinfo.turn == PLAYER_ONE) {
							SwapTiles(&game->ui.tilebar);
							game->gameinfo.player1consecutivePasses++;
							game->gameinfo.turn = PLAYER_TWO;
						} 
						else {
							SwapTiles(&game->ui.player2orAI);
							game->gameinfo.player2consecutivePasses++;
							game->gameinfo.turn = PLAYER_ONE;
						}
					}

				} else {
					// game->ui.tilebar.highlightedRectIndex = -1;
					// game->gameinfo.tileSelected = false;
				}

				if (game->gameinfo.turn == PLAYER_ONE) {

				}

				// check if selected board tile
				if ((game->gameinfo.tileSelected) && (mousepos.y < 810)) {
					if (game->gameinfo.turn == PLAYER_ONE) {
						SelectBoardTile(game, mousepos);
						PlaceTile(&game->gameinfo, &game->ui.board);
						game->gameinfo.tileSelected = false;
						game->ui.tilebar.playerTiles[game->ui.tilebar.highlightedRectIndex].placed = true;
						game->ui.tilebar.highlightedRectIndex = -1;					
					} else {
						SelectBoardTile(game, mousepos);
						PlaceTile(&game->gameinfo, &game->ui.board);
						game->gameinfo.tileSelected = false;
						game->ui.player2orAI.playerTiles[game->ui.player2orAI.highlightedRectIndex].placed = true;
						game->ui.player2orAI.highlightedRectIndex = -1;				
					} 
					

				}



			// right click
			} else if (event.button.button == SDL_BUTTON_RIGHT) {
				//
			}

		default:
			break;
	}
}

void DisplayWinner(Game *game) {
	if (game->gameinfo.player1score > game->gameinfo.player2score) printf("Player 1 Wins!\n");
	else if (game->gameinfo.player2score < game->gameinfo.player2score) printf("Player 2 Wins!\n");
	else printf("You tied!\n");
}

void Update_Singleplayer(Game *game) {
	if (game->gameinfo.player1consecutivePasses >= 3) {
		printf("Player 1 passed too many times!\n");
		printf("The computer wins!\n");
		PrintScore(game);
		game->gameinfo.isRunning = false;

	}

	if (game->gameinfo.player2consecutivePasses >= 3) {
		printf("The computer has passed too many times!\n");
		printf("You win!\n");
		PrintScore(game);
		game->gameinfo.isRunning = false;

	}


	if (game->gameinfo.turn == AI) {
		// printf("~~~~~~");
		// fflush(stdout);
		AI_Move(game);
		PrintScore(game);
		game->gameinfo.turn = PLAYER;
	}

	if (numTilesRemaining == 0) {
		DisplayWinner(game);
		game->gameinfo.isRunning = false;
	}
	return;
}

void Update_Multiplayer(Game *game) {
	if (game->gameinfo.player1consecutivePasses >= 3) {
		printf("Player 1 passed too many times!\n");
		printf("The computer wins!\n");
		PrintScore(game);
		game->gameinfo.isRunning = false;
	}

	if (game->gameinfo.player2consecutivePasses >= 3) {
		printf("The computer has passed too many times!\n");
		printf("You win!\n");
		PrintScore(game);
		game->gameinfo.isRunning = false;
	}

}

void Render(Game *game) {

	// printf("%d\n", numcount);

	// printf("SEGFAULT TEST 1\n");

	SDL_RenderClear(game->renderer);

	// past this line is where stuff to render goes

	// render the board
	// including locked in tiles
	SDL_RenderCopy(game->renderer, game->ui.board.centerTileTex, NULL, &game->ui.board.boardRects[7][7]);
    for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (game->ui.board.boardTiles[i][j].occupied == true) {
				SDL_RenderCopy(game->renderer, game->ui.board.boardTiles[i][j].tile->tileTex, NULL, &game->ui.board.boardRects[i][j]);
			} else {
    			SDL_RenderCopy(game->renderer, game->ui.board.boardTileTex, NULL, &game->ui.board.boardRects[i][j]);
				if (i == game->ui.board.center && j == game->ui.board.center) SDL_RenderCopy(game->renderer, game->ui.board.centerTileTex, NULL, &game->ui.board.boardRects[game->ui.board.center][game->ui.board.center]);
			}
    	}
	}

	// render the staged tiles
	if (game->ui.board.numStagedTiles != 0) {
		// printf("Do we segfault here? num staged = %d\n", game->ui.board.numStagedTiles);
		for (int i = 0; i < game->ui.board.numStagedTiles; i++) {
			// printf("%d segfault?\n", i);
			StagedTile *st = game->ui.board.stagedTiles[i];
			// if (i == 3) {
			// 	// printf("%d %d %d\n", st->tile, st->x_pos, st->y_pos);
			// }
			SDL_RenderCopy(game->renderer, game->ui.letters[st->tile].tileTex, NULL, &game->ui.board.boardRects[st->x_pos][st->y_pos]);
		}
	}
	
	// printf("SEGFAULT TEST 3\n");

	// render UI

	SDL_RenderCopy(game->renderer, game->ui.tilebar.submitButtonTex, NULL, &game->ui.tilebar.submitButtonRect);
	SDL_RenderCopy(game->renderer, game->ui.tilebar.swapButtonTex, NULL, &game->ui.tilebar.swapButtonRect);


    // check for selectedTile, render it if so
    if (game->ui.tilebar.highlightedRectIndex >= 0) {
    	SDL_RenderCopy(game->renderer, game->ui.tilebar.highlightTex, NULL, &game->ui.tilebar.tileSlotRects[game->ui.tilebar.highlightedRectIndex]);   	
    }

	// printf("SEGFAULT TEST 4\n");
    // render the tiles in the players tile bar
	for (int i = 0; i < 7; i ++) {
		if (game->ui.tilebar.playerTiles[i].placed == false) {
			SDL_RenderCopy(game->renderer, game->ui.letters[game->ui.tilebar.playerTiles[i].val].tileTex, NULL, &game->ui.tilebar.tileRects[i]);
		}
	}

 
	// printf("SEGFAULT TEST 5\n");

	// nothing should be after render present
	SDL_RenderPresent(game->renderer);

	return;
}


void RenderMP(Game *game) {

	// printf("%d\n", numcount);

	// printf("SEGFAULT TEST 1\n");

	SDL_RenderClear(game->renderer);

	// past this line is where stuff to render goes

	// render the board
	// including locked in tiles
	SDL_RenderCopy(game->renderer, game->ui.board.centerTileTex, NULL, &game->ui.board.boardRects[7][7]);
    for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (game->ui.board.boardTiles[i][j].occupied == true) {
				SDL_RenderCopy(game->renderer, game->ui.board.boardTiles[i][j].tile->tileTex, NULL, &game->ui.board.boardRects[i][j]);
			} else {
    			SDL_RenderCopy(game->renderer, game->ui.board.boardTileTex, NULL, &game->ui.board.boardRects[i][j]);
				if (i == game->ui.board.center && j == game->ui.board.center) SDL_RenderCopy(game->renderer, game->ui.board.centerTileTex, NULL, &game->ui.board.boardRects[game->ui.board.center][game->ui.board.center]);
			}
    	}
	}

	// render the staged tiles
	if (game->ui.board.numStagedTiles != 0) {
		// printf("Do we segfault here? num staged = %d\n", game->ui.board.numStagedTiles);
		for (int i = 0; i < game->ui.board.numStagedTiles; i++) {
			// printf("%d segfault?\n", i);
			StagedTile *st = game->ui.board.stagedTiles[i];
			// if (i == 3) {
			// 	// printf("%d %d %d\n", st->tile, st->x_pos, st->y_pos);
			// }
			SDL_RenderCopy(game->renderer, game->ui.letters[st->tile].tileTex, NULL, &game->ui.board.boardRects[st->x_pos][st->y_pos]);
		}
	}
	
	// printf("SEGFAULT TEST 3\n");

	// render UI

	SDL_RenderCopy(game->renderer, game->ui.tilebar.submitButtonTex, NULL, &game->ui.tilebar.submitButtonRect);
	SDL_RenderCopy(game->renderer, game->ui.tilebar.swapButtonTex, NULL, &game->ui.tilebar.swapButtonRect);

    // check for selectedTile, render it if so


	// printf("SEGFAULT TEST 4\n");
    // render the tiles in the players tile bar
	if (game->gameinfo.turn == PLAYER_ONE) {
		if (game->ui.tilebar.highlightedRectIndex >= 0) {
    		SDL_RenderCopy(game->renderer, game->ui.tilebar.highlightTex, NULL, &game->ui.tilebar.tileSlotRects[game->ui.tilebar.highlightedRectIndex]);   	
   		}
		for (int i = 0; i < 7; i ++) {
			if (game->ui.tilebar.playerTiles[i].placed == false) {
				SDL_RenderCopy(game->renderer, game->ui.letters[game->ui.tilebar.playerTiles[i].val].tileTex, NULL, &game->ui.tilebar.tileRects[i]);
			}
		}
	} else {
		if (game->ui.player2orAI.highlightedRectIndex >= 0) {
    		SDL_RenderCopy(game->renderer, game->ui.player2orAI.highlightTex, NULL, &game->ui.player2orAI.tileSlotRects[game->ui.player2orAI.highlightedRectIndex]);   	
   		}
		for (int i = 0; i < 7; i ++) {
			if (game->ui.player2orAI.playerTiles[i].placed == false) {
				SDL_RenderCopy(game->renderer, game->ui.letters[game->ui.player2orAI.playerTiles[i].val].tileTex, NULL, &game->ui.player2orAI.tileRects[i]);
			}
		}
	}


 
	// printf("SEGFAULT TEST 5\n");

	// nothing should be after render present
	SDL_RenderPresent(game->renderer);

	return;
}

void Clean(Game* game) {
	SDL_DestroyWindow(game->window);
	SDL_DestroyRenderer(game->renderer);
	// free(game->ui);
	// free(game->letters);
	SDL_Quit();
	printf("Game cleaned.\n");
	return;
}

// check if mouse has clicked an item in my players hand
void checkPlayerTileClick(Position mousePos, Tile *location) {


	return;
}