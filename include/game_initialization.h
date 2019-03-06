#pragma once
#include "../include/types.h"


// void LoadTiles(Tile *array, SDL_Renderer *renderer);
Tile * LoadTiles(SDL_Renderer *renderer);

// void LoadPlayerTiles(Tile *, Tile *);
Tile * LoadPlayerTiles(Tile *letters);

void InitTileBarRects(Game *game);

void InitBoardRects(Game *game);