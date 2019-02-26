#include "../include/game2.h"
#include <stdlib.h>

SDL_Texture* LoadTexture(const char* texture, SDL_Renderer* ren) {
        SDL_Surface *tempSurface = IMG_Load(texture);
        SDL_Texture *tex = SDL_CreateTextureFromSurface(ren, tempSurface);
        SDL_FreeSurface(tempSurface);
        return tex;
}


void Init(Game* game, const char* title, int xpos, int ypos, int width, int height, bool fullScreen) {
	int flags = 0;

	if (fullScreen) flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		// std::cout << "Subsystems Initialized..." << std::endl;
		printf("Subsystems initialized...\n");

		game->window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (game->window) { // confirm window was created
			printf("Window created!\n");
		}

		game->ui.board.boardRect.w = 800;
		game->ui.board.boardRect.h = 800;
		LoadTiles(game->letters, game->renderer);
		LoadPlayerTiles(game->ui.tileBar.playerTiles, game->letters);


		game->renderer = SDL_CreateRenderer(game->window, -1, 0);



		game->ui.board.boardTex = LoadTexture("resources/scrabbleBoard.jpg", game->renderer);

		// printf("$$$\n");
		// game->ui->TileBar = constructTileBar();

		if (game->renderer) { // confirm renderer was created
			SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 255);
			printf("Renderer created!\n");
		}

		game->isRunning = true;
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
	SDL_RenderPresent(game->renderer);
	return;
}

void Clean(Game* game) {
	SDL_DestroyWindow(game->window);
	SDL_DestroyRenderer(game->renderer);
	SDL_Quit();
	printf("Game cleaned.\n");
	return;
}


void LoadTiles(Tile *array, SDL_Renderer *renderer) {
	array = (Tile*)malloc(sizeof(Tile) * 26);

	for (int i = 0; i<26; i++) {
		array[i].letter = 65 + i;
		array[i].tileRect.w = 100;
		array[i].tileRect.h = 100;
	}

	array[0].tileTex = LoadTexture("resources/tiles/A.png", renderer);
	array[1].tileTex = LoadTexture("resources/tiles/B.png", renderer);
	array[2].tileTex = LoadTexture("resources/tiles/C.png", renderer);
	array[3].tileTex = LoadTexture("resources/tiles/D.png", renderer);
	array[4].tileTex = LoadTexture("resources/tiles/E.png", renderer);
	array[5].tileTex = LoadTexture("resources/tiles/F.png", renderer);
	array[6].tileTex = LoadTexture("resources/tiles/G.png", renderer);
	array[7].tileTex = LoadTexture("resources/tiles/H.png", renderer);
	return;
}

void LoadPlayerTiles(Tile *ptiles, Tile *set) {
	ptiles = (Tile *)malloc(sizeof(Tile) * 7);

	for (int i = 0; i<7; i++) {
		int x = rand() % 7;
		printf("%d\n", x);
	}

	for (int i = 0; i < 7; i++) {
		printf("%d", set[i]->letter);
	}

	// for (int i = 0; i < 7; i++) {
	// 	int x = rand() % 7;
	// 	printf("%d", x);
	// 	ptiles[i] = set[x];
	// }

	return;
}