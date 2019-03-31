#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>
#include "graph.h"
#include "trie.h"
#include "heap.h"

// size of the board
int BOARD_SIZE;

// maximum index along x or y axis
int MAXIMUM_INDEX;

// alphabet string used for appending letters by index
static char ALPHABET[26] = "abcdefghijklmnopqrstuvwxyz";

// root of the trie
TrieNode *root;

// tilebag
static int tileBag[26] = {9, 2, 2, 4, 12, 2, 3, 2, 9, 1, 1 ,4, 2, 6, 8, 2, 1, 6, 6, 6, 4, 2, 2, 1, 2, 1};

// num of tiles remaining
int numTilesRemaining;



// ENUMERATED TYPES

enum direction {
	VERTICAL = true,
	HORIZONTAL = false
};

enum gametype {
	NONE = 0,
	SINGLEPLAYER = 1,
	MULTIPLAYER = 2
};

enum connectType {
	CT_INVALID = 0,
	CT_VALID = 1,
	CT_NONE = 2
};

enum turnType {
	PLAYER = 1,
	PLAYER_ONE = 1,
	PLAYER_TWO = 2,
	AI = 3
};


// GAME ORGANIZATION STRUCTS

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
	bool valid;
	Tile *tile;
	AdjacencyNode *VerticalAdjacency;
	AdjacencyNode *HorizontalAdjacency;
} TileSlot;

typedef struct Board {
	int numStagedTiles;
	int numAIstagedTiles;
	int center;
	SDL_Texture *boardTileTex;
	SDL_Texture *centerTileTex;
	SDL_Rect boardRect;
	// SDL_Rect *boardRects[][]; // need to make board variable size
	// TileSlot *boardTiles[][];
	SDL_Rect boardRects[15][15];
	TileSlot boardTiles[15][15];
	AdjacencyNode *tempAdjacencies;
	AdjacencyNode *adjacencyListHead;
	StagedTile *stagedTiles[50];
	StagedTile *AIstagedTiles[50];
} Board;

typedef struct pTiles {
	// range 0-25
	int val;
	bool placed;
} pTiles;

typedef struct TileBar {
	int highlightedRectIndex;
	pTiles playerTiles[7];
	SDL_Texture *tileBarTex;
	SDL_Texture *highlightTex;
	SDL_Texture *submitButtonTex;
	SDL_Rect submitButtonRect;
	SDL_Rect tileRects[7];
	SDL_Rect tileSlotRects[7];
} TileBar;

typedef struct Menu {
	SDL_Texture *menuTex;
	SDL_Texture *singlelayerButtonTex;
	SDL_Texture *mutliplayerButtonTex;
	SDL_Texture *boardSizeButtonTex;
	SDL_Rect menuRect;
	SDL_Rect singlePlayerButtonRect;
	SDL_Rect multiplayerButtonRect;
	SDL_Rect boardSizeButtonRect;
} Menu;

typedef struct UserInterface {
	Menu menu;
	TileBar tilebar;
	TileBar player2orAI;
	Board board;
	Tile *letters;
	Tile *boardTiles;
} UserInterface;

typedef struct Position {
	int x;
	int y;
} Position;

typedef struct GameInfo {
	int turn;
	int board_size;
	int selectedTile;
	bool isRunning;
	bool tileSelected;
	bool gamemode;
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

