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
	bool selected;
	Tile *tile;
} TileSlot;


typedef struct Board {
	SDL_Texture *boardTex;
	SDL_Rect boardRect;
	TileSlot boardTiles[15][15];
} Board;

typedef struct TileBar {
	SDL_Texture *tileBarTex;
	SDL_Texture *highlightTex;
	Tile *playerTiles;
	SDL_Rect tileRects[7];
	SDL_Rect tileSlotRects[7];
	int highlightedRectIndex;
} TileBar;

typedef struct UI {
	Board board;
	TileBar tilebar;
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