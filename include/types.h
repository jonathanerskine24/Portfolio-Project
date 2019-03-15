#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

typedef struct GameParameters {
	int BOARD_WIDTH;
	int BOARD_HEIGHT;
	int WINDOW_WIDTH;
	int WINDOW_HEIGHT;
} GameParameters;

typedef struct Tile {
	char letter;
	int value;
	SDL_Texture *tileTex;
	SDL_Rect tileRect;
} Tile;

typedef struct StagedTile {
	int tile;
	int x_pos;
	int y_pos;
} StagedTile;

typedef struct TileSlot {
	int x_coord;
	int y_coord;
	bool validConnection;
	bool occupied;
	bool selected;
	Tile *tile;
} TileSlot;

typedef struct Board {
	SDL_Texture *boardTileTex;
	SDL_Texture *centerTileTex;
	SDL_Rect boardRect;
	// SDL_Rect *boardRects[][]; // need to make board variable size
	// TileSlot *boardTiles[][];
	SDL_Rect boardRects[15][15];
	TileSlot boardTiles[15][15];
	int numStagedTiles;
	StagedTile *stagedTiles[100];
} Board;

typedef struct TileBar {
	SDL_Texture *tileBarTex;
	SDL_Texture *highlightTex;
	// Tile *playerTiles;
	int playerTiles[7];
	SDL_Rect tileRects[7];
	SDL_Rect tileSlotRects[7];
	int highlightedRectIndex;
} TileBar;

typedef struct UI {
	TileBar tilebar;
	Board board;
} UI;

typedef struct Position {
	int x;
	int y;
} Position;

typedef struct Game {
	int board_size;
	GameParameters params;
	SDL_Window *window;
	SDL_Renderer *renderer;
	Tile *letters;
	int selectedTile;
	Position selectedBoardTile;
	bool isRunning;
	bool tileSelected;
	UI ui;
} Game;

