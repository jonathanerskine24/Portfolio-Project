#include "../include/game_initialization.h"
#include "../include/game2.h"

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

	game->letters = array;
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
		game->ui.tilebar.tileRects[i].y = game->params.BOARD_HEIGHT + 5;
		game->ui.tilebar.tileSlotRects[i].h = 100;
		game->ui.tilebar.tileSlotRects[i].w = 100;
		game->ui.tilebar.tileSlotRects[i].x = (i*100);
		game->ui.tilebar.tileSlotRects[i].y = game->params.BOARD_HEIGHT;
	}
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

void InitializeGame(Game *game) {
	game->isRunning = true;
	game->tileSelected = false;
	game->selectedTile = NULL;
	game->ui.board.boardRect.w = game->params.BOARD_WIDTH;
	game->ui.board.boardRect.h = game->params.BOARD_HEIGHT;
	game->ui.tilebar.highlightedRectIndex = -1;
	printf("Loading textures...\n");
	game->ui.board.boardTileTex = LoadTexture("resources/boardTile.jpg", game->renderer);
	game->ui.tilebar.highlightTex = LoadTexture("resources/highlight.jpg", game->renderer);
	game->ui.board.centerTileTex = LoadTexture("resources/centerTile.jpg", game->renderer);
	printf("Loading Tiles...\n");
	LoadTiles(game);
	LoadPlayerTiles(game);
	printf("Initializing board...\n");
	InitTileBarRects(game);
	InitBoardRects(game);
	printf("Loading dictionary...\n");
	LoadDictionary();
	printf("Done.\n");

}