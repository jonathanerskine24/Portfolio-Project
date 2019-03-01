#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

typedef struct Tile {
	char letter;
	int value;
	SDL_Texture *tileTex;
	SDL_Rect tileRect;
} Tile;

typedef struct TileSlot {
	int x_coord;
	int y_coord;
	bool validConnection;
	bool occupied;
	Tile *tile;
} TileSlot;


typedef struct Board {
	SDL_Texture *boardTex;
	SDL_Rect boardRect;
	TileSlot boardTiles[15][15];
} Board;

typedef struct TileBar {
	SDL_Texture *tileBarTex;
	Tile *playerTiles;
	SDL_Rect tileRects[7];
} TileBar;

typedef struct UI {
	Board board;
	TileBar tileBar;
} UI;

typedef struct Game {
	SDL_Window *window;
	SDL_Renderer *renderer;
	UI ui;
	Tile *letters;
	Tile *selectedTile;
	bool isRunning;
} Game;

typedef struct Position {
	int x;
	int y;
} Position;