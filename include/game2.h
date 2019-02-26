#pragma once
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

typedef struct Tile {
	char letter;
	int value;
	SDL_Texture *tileTex;
	SDL_Rect tileRect;
} Tile;


typedef struct Board {
	SDL_Texture *boardTex;
	SDL_Rect boardRect;
} Board;

typedef struct TileBar {
	SDL_Rect tileBarRect;
	SDL_Texture *tileBarText;
	Tile *playerTiles;
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
	bool isRunning;
} Game;


void Init(Game* game, const char* title, int xpos, int ypos, int width, int height, bool fullScreen);

void HandleEvents(Game *game);

void Update(Game *game);

void Render(Game *game);

void Clean(Game *game);

void LoadTiles(Tile *array, SDL_Renderer *renderer);

void LoadPlayerTiles(Tile *, Tile *);