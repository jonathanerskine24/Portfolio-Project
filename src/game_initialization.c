#include "../include/game_initialization.h"
#include "../include/game2.h"

Tile* LoadTiles(SDL_Renderer *renderer) {
	Tile *array = (Tile*)malloc(sizeof(Tile) * 26);

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


	// for (int i = 0; i < 7; i++) {
	// 	printf("%c", array[i].letter);
	// }

	return array;
}

Tile* LoadPlayerTiles(Tile *set) {
	Tile *ptiles = (Tile *)malloc(sizeof(Tile) * 7);

	for (int i = 0; i<7; i++) {
		int x = rand() % 7;
		ptiles[i] = set[x];
	}

	return ptiles;
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
