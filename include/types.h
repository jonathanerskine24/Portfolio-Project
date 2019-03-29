#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "graph.h"
#include "trie.h"

int BOARD_SIZE;
static char ALPHABET[26] = "abcdefghijklmnopqrstuvwxyz";
TrieNode *root;

enum direction {
	VERTICAL = true,
	HORIZONTAL = false
};

enum connectType {
	CT_INVALID = 0,
	CT_VALID = 1,
	CT_NONE = 2
};

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
	int stval; // staged tile val
	bool occupied;
	bool selected;
	Tile *tile;
	AdjacencyNode *VerticalAdjacency;
	AdjacencyNode *HorizontalAdjacency;
} TileSlot;

typedef struct Board {
	int numStagedTiles;
	int center;
	SDL_Texture *boardTileTex;
	SDL_Texture *centerTileTex;
	SDL_Rect boardRect;
	// SDL_Rect *boardRects[][]; // need to make board variable size
	// TileSlot *boardTiles[][];
	SDL_Rect boardRects[15][15];
	TileSlot boardTiles[15][15];
	AdjacencyNode *tempAdjacencies;
	StagedTile *stagedTiles[100];
} Board;

typedef struct TileBar {
	int highlightedRectIndex;
	int playerTiles[7];
	SDL_Texture *tileBarTex;
	SDL_Texture *highlightTex;
	SDL_Texture *submitButtonTex;
	SDL_Rect submitButtonRect;
	SDL_Rect tileRects[7];
	SDL_Rect tileSlotRects[7];
} TileBar;

typedef struct UserInterface {
	TileBar tilebar;
	Board board;
	Tile *letters;
	Tile *boardTiles;
} UserInterface;

typedef struct Position {
	int x;
	int y;
} Position;

typedef struct GameInfo {
	int board_size;
	int selectedTile;
	bool isRunning;
	bool tileSelected;
	bool wordDirection; 
	Position selectedBoardTile;
	GameParameters params;
} GameInfo;

typedef struct Game {
	SDL_Window *window;
	SDL_Renderer *renderer;
	GameInfo gameinfo;
	UserInterface ui;
} Game;

