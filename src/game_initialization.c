#include "../include/game_initialization.h"
#include "../include/game2.h"

SDL_Rect InitRect(int w, int h, int x, int y) {
	SDL_Rect r;
	r.h = h;
	r.w = w;
	r.x = x;
	r.y = y;
	return r;
}

void LoadTiles(Game *game) {

	Tile *array = (Tile*)malloc(sizeof(Tile) * 26);

	for (int i = 0; i<26; i++) {
		array[i].letter = 65 + i;
		array[i].tileRect.w = 100;
		array[i].tileRect.h = 100;
	}

	array[0].tileTex = LoadTexture("resources/tiles/A.png", game->renderer);
	array[1].tileTex = LoadTexture("resources/tiles/B.png", game->renderer);
	array[2].tileTex = LoadTexture("resources/tiles/C.png", game->renderer);
	array[3].tileTex = LoadTexture("resources/tiles/D.png", game->renderer);
	array[4].tileTex = LoadTexture("resources/tiles/E.png", game->renderer);
	array[5].tileTex = LoadTexture("resources/tiles/F.png", game->renderer);
	array[6].tileTex = LoadTexture("resources/tiles/G.png", game->renderer);
	array[7].tileTex = LoadTexture("resources/tiles/H.png", game->renderer);


	// for (int i = 0; i < 7; i++) {
	// 	printf("%c", array[i].letter);
	// }

	game->ui.letters = array;
	// return array;
	return;
}

void LoadPlayerTiles(Game *game) {

	for (int i = 0; i<7; i++) {
		game->ui.tilebar.playerTiles[i] = rand() % 8;
	}

	return;
}

void InitTileBarRects(Game *game) {
	for (int i = 0; i < 7; i++) {
		game->ui.tilebar.tileRects[i].h = 90;
		game->ui.tilebar.tileRects[i].w = 90;
		game->ui.tilebar.tileRects[i].x = 5+ (i * 100);
		game->ui.tilebar.tileRects[i].y = game->gameinfo.params.BOARD_HEIGHT + 5;
		game->ui.tilebar.tileSlotRects[i].h = 100;
		game->ui.tilebar.tileSlotRects[i].w = 100;
		game->ui.tilebar.tileSlotRects[i].x = (i*100);
		game->ui.tilebar.tileSlotRects[i].y = game->gameinfo.params.BOARD_HEIGHT;
	}

	game->ui.tilebar.submitButtonRect = InitRect(85, 45, 700 + 10, game->gameinfo.params.BOARD_HEIGHT + 10);
	return;

}

void InitBoardRects(Game *game) {
	for (int i = 0; i < 15; i++) {
		for (int j = 0; j < 15; j++) {
			game->ui.board.boardRects[i][j].w = 54;
			game->ui.board.boardRects[i][j].h = 54;
			game->ui.board.boardRects[i][j].x = i*54;
			game->ui.board.boardRects[i][j].y = j*54;
		}
	}	
	return;
}

void InitBoard(Game *game) {
	InitBoardRects(game);



	// for (int i = 0; i < game->board_size; i++) {
	// 	game->ui.board.stagedTiles[i] = malloc(sizeof(StagedTile*));
	// }

	game->ui.board.numStagedTiles = 0;
	return;
}

void LoadGameTextures(UserInterface* ui, SDL_Renderer* ren) {
	ui->board.boardTileTex = LoadTexture("resources/boardTile.jpg", ren);
	ui->tilebar.highlightTex = LoadTexture("resources/highlight.jpg", ren);
	ui->board.centerTileTex = LoadTexture("resources/centerTile.jpg", ren);
	ui->tilebar.submitButtonTex = LoadTexture("resources/submitButton.jpg", ren);
	return;	
}

void InitializeGame(Game *game) {
	game->gameinfo.isRunning = true;
	// printf("FILE: %s FUNCTION: %s LINE: %d\n ", __FILE__, __func__, __LINE__);
	game->gameinfo.tileSelected = false;
	game->gameinfo.selectedTile = NULL;
	game->ui.board.boardRect.w = game->gameinfo.params.BOARD_WIDTH;
	game->ui.board.boardRect.h = game->gameinfo.params.BOARD_HEIGHT;
	game->ui.tilebar.highlightedRectIndex = -1;
	printf("Loading textures...\n");
	LoadGameTextures(&game->ui, game->renderer);
	printf("Loading Tiles...\n");
	LoadTiles(game);
	LoadPlayerTiles(game);
	printf("Initializing board...\n");
	InitTileBarRects(game);
	InitBoardRects(game);
	printf("Loading dictionary...\n");
	Render(game);
	LoadDictionary();
	printf("Done.\n");

}