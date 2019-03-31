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

	numTilesRemaining = 100;

	Tile *array = (Tile*)malloc(sizeof(Tile) * 26);

	for (int i = 0; i<26; i++) {
		array[i].letter = 97 + i;
		array[i].tileRect.w = 100;
		array[i].tileRect.h = 100;
	}

	array[0].tileTex = LoadTexture("resources/tiles/A_hand.png", game->renderer);
	array[1].tileTex = LoadTexture("resources/tiles/B_hand.png", game->renderer);
	array[2].tileTex = LoadTexture("resources/tiles/C_hand.png", game->renderer);
	array[3].tileTex = LoadTexture("resources/tiles/D_hand.png", game->renderer);
	array[4].tileTex = LoadTexture("resources/tiles/E_hand.png", game->renderer);
	array[5].tileTex = LoadTexture("resources/tiles/F_hand.png", game->renderer);
	array[6].tileTex = LoadTexture("resources/tiles/G_hand.png", game->renderer);
	array[7].tileTex = LoadTexture("resources/tiles/H_hand.png", game->renderer);
	array[8].tileTex = LoadTexture("resources/tiles/I_hand.png", game->renderer);
	array[9].tileTex = LoadTexture("resources/tiles/J_hand.png", game->renderer);
	array[10].tileTex = LoadTexture("resources/tiles/K_hand.png", game->renderer);
	array[11].tileTex = LoadTexture("resources/tiles/L_hand.png", game->renderer);
	array[12].tileTex = LoadTexture("resources/tiles/M_hand.png", game->renderer);
	array[13].tileTex = LoadTexture("resources/tiles/N_hand.png", game->renderer);
	array[14].tileTex = LoadTexture("resources/tiles/O_hand.png", game->renderer);
	array[15].tileTex = LoadTexture("resources/tiles/P_hand.png", game->renderer);
	array[16].tileTex = LoadTexture("resources/tiles/Q_hand.png", game->renderer);
	array[17].tileTex = LoadTexture("resources/tiles/R_hand.png", game->renderer);
	array[18].tileTex = LoadTexture("resources/tiles/S_hand.png", game->renderer);
	array[19].tileTex = LoadTexture("resources/tiles/T_hand.png", game->renderer);
	array[20].tileTex = LoadTexture("resources/tiles/U_hand.png", game->renderer);
	array[21].tileTex = LoadTexture("resources/tiles/V_hand.png", game->renderer);
	array[22].tileTex = LoadTexture("resources/tiles/W_hand.png", game->renderer);
	array[23].tileTex = LoadTexture("resources/tiles/X_hand.png", game->renderer);
	array[24].tileTex = LoadTexture("resources/tiles/Y_hand.png", game->renderer);
	array[25].tileTex = LoadTexture("resources/tiles/Z_hand.png", game->renderer);


	game->ui.letters = array;
	return;
}

void LoadBoardTiles(Game *game) {
	Tile *array = (Tile*)malloc(sizeof(Tile) * 26);

	for (int i = 0; i<26; i++) {
		array[i].letter = 97 + i;
		array[i].tileRect.w = 100;
		array[i].tileRect.h = 100;
	}

	array[0].tileTex = LoadTexture("resources/tiles/A_board.png", game->renderer);
	array[1].tileTex = LoadTexture("resources/tiles/B_board.png", game->renderer);
	array[2].tileTex = LoadTexture("resources/tiles/C_board.png", game->renderer);
	array[3].tileTex = LoadTexture("resources/tiles/D_board.png", game->renderer);
	array[4].tileTex = LoadTexture("resources/tiles/E_board.png", game->renderer);
	array[5].tileTex = LoadTexture("resources/tiles/F_board.png", game->renderer);
	array[6].tileTex = LoadTexture("resources/tiles/G_board.png", game->renderer);
	array[7].tileTex = LoadTexture("resources/tiles/H_board.png", game->renderer);
	array[8].tileTex = LoadTexture("resources/tiles/I_board.png", game->renderer);
	array[9].tileTex = LoadTexture("resources/tiles/J_board.png", game->renderer);
	array[10].tileTex = LoadTexture("resources/tiles/K_board.png", game->renderer);
	array[11].tileTex = LoadTexture("resources/tiles/L_board.png", game->renderer);
	array[12].tileTex = LoadTexture("resources/tiles/M_board.png", game->renderer);
	array[13].tileTex = LoadTexture("resources/tiles/N_board.png", game->renderer);
	array[14].tileTex = LoadTexture("resources/tiles/O_board.png", game->renderer);
	array[15].tileTex = LoadTexture("resources/tiles/P_board.png", game->renderer);
	array[16].tileTex = LoadTexture("resources/tiles/Q_board.png", game->renderer);
	array[17].tileTex = LoadTexture("resources/tiles/R_board.png", game->renderer);
	array[18].tileTex = LoadTexture("resources/tiles/S_board.png", game->renderer);
	array[19].tileTex = LoadTexture("resources/tiles/T_board.png", game->renderer);
	array[20].tileTex = LoadTexture("resources/tiles/U_board.png", game->renderer);
	array[21].tileTex = LoadTexture("resources/tiles/V_board.png", game->renderer);
	array[22].tileTex = LoadTexture("resources/tiles/W_board.png", game->renderer);
	array[23].tileTex = LoadTexture("resources/tiles/X_board.png", game->renderer);
	array[24].tileTex = LoadTexture("resources/tiles/Y_board.png", game->renderer);
	array[25].tileTex = LoadTexture("resources/tiles/Z_board.png", game->renderer);


	game->ui.boardTiles = array;
	return;
}



void LoadPlayerTiles(Game *game) {

	// random tiles
	for (int i = 0; i<7; i++) {
		game->ui.tilebar.playerTiles[i].val = SelectTile();
		game->ui.tilebar.playerTiles[i].placed = false;
	}

	// set tiles for testing
	// game->ui.tilebar.playerTiles[0].val = 0;
	// game->ui.tilebar.playerTiles[1].val = 4;
	// game->ui.tilebar.playerTiles[2].val = 3;
	// game->ui.tilebar.playerTiles[3].val = 12;
	// game->ui.tilebar.playerTiles[4].val = 13;
	// game->ui.tilebar.playerTiles[5].val = 8;
	// game->ui.tilebar.playerTiles[6].val = 11;


	return;
}

void LoadPlayer2AITiles(Game * game) {
	game->ui.board.numAIstagedTiles = 0;
	for (int i = 0; i<7; i++) {
		game->ui.player2orAI.playerTiles[i].val = SelectTile();
		game->ui.player2orAI.playerTiles[i].placed = false;
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
			game->ui.board.boardTiles[i][j].stval = -1;
			// game->ui.board.boardTiles[i][i].tile->value = -1;
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


	game->ui.board.numStagedTiles = 0;
	game->ui.board.tempAdjacencies = malloc(sizeof(AdjacencyNode));
	game->ui.board.adjacencyListHead = malloc(sizeof(AdjacencyNode));
	return;
}

void LoadMenuRects(UserInterface *ui) {
	ui->menu.menuRect = InitRect(800, 800, 0, 0);
	ui->menu.boardSizeButtonRect = InitRect(128, 64, 336, 550);
	ui->menu.multiplayerButtonRect = InitRect(128, 64, 536, 450);
	ui->menu.singlePlayerButtonRect = InitRect(128, 64, 126, 450);
	return;
}

void LoadMenuTextures(UserInterface *ui, SDL_Renderer *ren) {
	ui->menu.menuTex = LoadTexture("resources/Background.png", ren);
	ui->menu.boardSizeButtonTex = LoadTexture("resources/BoardSizeButton.png", ren);
	ui->menu.mutliplayerButtonTex = LoadTexture("resources/MultiplayerButton.png", ren);
	ui->menu.singlelayerButtonTex = LoadTexture("reources/SinglePlayerButton.png", ren);
	return;
}

void LoadGameTextures(UserInterface* ui, SDL_Renderer* ren) {
	ui->board.boardTileTex = LoadTexture("resources/boardTile.jpg", ren);
	ui->tilebar.highlightTex = LoadTexture("resources/highlight.jpg", ren);
	ui->board.centerTileTex = LoadTexture("resources/centerTile.jpg", ren);
	ui->tilebar.submitButtonTex = LoadTexture("resources/submitButton.jpg", ren);
	return;	
}

void InitializeMenu(Game *game) {
	game->gameinfo.isRunning = true;
	LoadMenuTextures(&game->ui, game->renderer);
	LoadMenuRects(&game->ui);
	return;
}

void InitializeGame(Game *game) {
	game->gameinfo.isRunning = true;
	game->gameinfo.tileSelected = false;
	game->gameinfo.selectedTile = NULL;
	game->ui.board.boardRect.w = game->gameinfo.params.BOARD_WIDTH;
	game->ui.board.boardRect.h = game->gameinfo.params.BOARD_HEIGHT;
	game->ui.tilebar.highlightedRectIndex = -1;
	printf("Loading textures...\n");
	LoadGameTextures(&game->ui, game->renderer);
	printf("Loading Tiles...\n");
	LoadTiles(game);
	LoadBoardTiles(game);
	LoadPlayerTiles(game);
	LoadPlayer2AITiles(game);
	printf("Initializing board...\n");
	InitTileBarRects(game);
	InitBoardRects(game);
	printf("Loading dictionary...\n");
	Render(game);
	LoadDictionaryTrie();

	printf("AI tiles: ");
	for (int i = 0; i < 7; i++) {
		printf("%c", ALPHABET[game->ui.player2orAI.playerTiles[i].val]);
	}
	printf("\n");

	printf("Done.\n");

}