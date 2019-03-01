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



// this currently causes inconsistent segfaults... not called in code at the moment
// for this reason
SDL_Rect* InitTileBarRects() {
	// arrayOfRects = (SDL_Rect*)malloc(sizeof(SDL_Rect*) * 7);
	SDL_Rect arrayOfRects[7];
	for (int i = 0; i < 7; i++) {
		arrayOfRects[i].h = 100;
		arrayOfRects[i].w = 100;
		arrayOfRects[i].x = i * 100;
		arrayOfRects[i].y = 800;
	}
	return arrayOfRects;
	// return arrayOfRects;
}