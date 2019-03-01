#include <stdlib.h>
#include <time.h>
#include "../include/game2.h"
#include "../include/game_initialization.h"
#include "../include/types.h"



SDL_Texture* LoadTexture(const char* texture, SDL_Renderer* ren) {
        SDL_Surface *tempSurface = IMG_Load(texture);
        SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, tempSurface);
        SDL_FreeSurface(tempSurface);
        return tex;
}


void Init(Game* game, const char* title, int xpos, int ypos, int width, int height, bool fullScreen) {

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

		game->ui.board.boardTex = LoadTexture("resources/scrabbleBoard.jpg", game->renderer);

		if (game->renderer) { // confirm renderer was created
			SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
			printf("Renderer created!\n");
		}

		game->isRunning = true;

		// do other stuff here
		game->selectedTile = NULL;
		game->ui.board.boardRect.w = BOARD_WIDTH;
		game->ui.board.boardRect.h = BOARD_HEIGHT;
		game->letters = LoadTiles(game->renderer);
		game->ui.tileBar.playerTiles = LoadPlayerTiles(game->letters);

		// InitTileBarRects(game->ui.tileBar.tileRects); // this code currently causes segfaults... fix
		// game->ui.tileBar.tileRects = InitTileBarRects();

		for (int i = 0; i < 7; i++) {
			game->ui.tileBar.tileRects[i].h = 90;
			game->ui.tileBar.tileRects[i].w = 90;
			game->ui.tileBar.tileRects[i].x = 5+ (i * 100);
			game->ui.tileBar.tileRects[i].y = 805;
		}


		// for (int i = 0; i < 7; i++) {
		// 	printf("%d ", i);
		// 	printf("%c\n ", game->letters[i].letter);
		// }


		for (int i = 0; i < 7; i ++) {
			// printf("**");
			printf("%c\n", game->ui.tileBar.playerTiles[i].letter);
		}




	} else {
		game->isRunning = false;
	}
}

void HandleEvents(Game* game) {

	printf("HANDLEEVENTS\n");

	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_QUIT:
			game->isRunning = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				case SDLK_RETURN:
					break;
			}
		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				Position mousepos;
				mousepos.x = event.button.x; mousepos.y = event.button.y;
				checkPlayerTileClick(mousepos, game->selectedTile);
			}

		default:
			break;
	}
}

void Update(Game * game) {

	return;
}

void Render(Game *game) {
	SDL_RenderClear(game->renderer);
	// this is where stuff to render goes
    SDL_RenderCopy(game->renderer, game->ui.board.boardTex, NULL,  &game->ui.board.boardRect);
    // render the tiles in the players tile bar
	for (int i = 0; i < 7; i ++) { 
		SDL_RenderCopy(game->renderer, game->ui.tileBar.playerTiles[i].tileTex, NULL, &game->ui.tileBar.tileRects[i]);
	}
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


// put this shit somewhere else vv

// void InitTileSlotArray(TileSlot *boardTiles[][]) {
// 	for (int i = 0; i < 15; i++) {
// 		for (int j = 0; j < 15; j++) {
// 			boardTiles[i][j]->x_coord = i;
// 			boardTiles[i][j]->y_coord = j;
// 			boardTiles[i][j]->validConnection = false;
// 			boardTiles[i][j]->occupied = false;
// 			boardTiles[i][j]->tile->tileRect.x = (51 * i) + (2 * i);
// 			boardTiles[i][j]->tile->tileRect.y = (51 * i) + (2 * i);
// 			boardTiles[i][j]->tile->tileRect.l = 51;
// 			boardTiles[i][j]->tile->tileRect.w = 51;
// 		}
// 	}
// 	return;
// }


// check if mouse has clicked an item in my players hand
void checkPlayerTileClick(Position mousePos, Tile *location) {
	// SDL_Rect *pieceR = piece->getRect();
	// int left, right, top, bottom;
	// left = pieceR->y;
	// right = pieceR->y + pieceR->w;
	// top = pieceR->x;
	// bottom = pieceR->x + pieceR->h;

	// if (mousePos.x < top) piece->setClicked(false);
	// else if (mousePos.x > bottom) piece->setClicked(false);
	// else if (mousePos.y > right) piece->setClicked(false);
	// else if (mousePos.y < left) piece->setClicked(false);


	return;
}