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

		if (game->renderer) { // confirm renderer was created
			SDL_SetRenderDrawColor(game->renderer, 27, 27, 27, 255);
			printf("Renderer created!\n");
		}

		InitializeGame(game);

	} else {
		game->isRunning = false;
	}
}

void HandleEvents(Game* game) {

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
			// left click
			if (event.button.button == SDL_BUTTON_LEFT) {
				Position mousepos;
				mousepos.x = event.button.x; mousepos.y = event.button.y;
				// printf("X %d , Y %d\n", mousepos.x, mousepos.y);	
				if (mousepos.y > 800) {
					game->ui.tilebar.highlightedRectIndex = mousepos.x / 100;
				} else {
					game->ui.tilebar.highlightedRectIndex = -1;
				}
				checkPlayerTileClick(mousepos, game->selectedTile);
			// right click
			} else if (event.button.button == SDL_BUTTON_RIGHT) {

			}

		default:
			break;
	}
}

void Update(Game * game) {
	// game->highlitedTile = game->ui.tilebar.highlightedRectIndex;
	return;
}

void Render(Game *game) {
	SDL_RenderClear(game->renderer);

	// past this line is where stuff to render goes
    for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
    		SDL_RenderCopy(game->renderer, game->ui.board.boardTileTex, NULL, &game->ui.board.boardRects[i][j]);
    	}
	}

    // check for selectedTile, render it if so
    if (game->ui.tilebar.highlightedRectIndex >= 0) {
    	SDL_RenderCopy(game->renderer, game->ui.tilebar.highlightTex, NULL, &game->ui.tilebar.tileSlotRects[game->ui.tilebar.highlightedRectIndex]);   	
    }
    // render the tiles in the players tile bar
	for (int i = 0; i < 7; i ++) { 
		SDL_RenderCopy(game->renderer, game->ui.tilebar.playerTiles[i].tileTex, NULL, &game->ui.tilebar.tileRects[i]);
	}

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