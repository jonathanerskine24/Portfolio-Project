#pragma once
#include "../include/types.h"


// void LoadTiles(Tile *array, SDL_Renderer *renderer);
// Tile * LoadTiles(SDL_Renderer *renderer);
void LoadTiles(Game *game);

// void LoadPlayerTiles(Tile *, Tile *);
// Tile * LoadPlayerTiles(Tile *letters);
void LoadPlayerTiles(Game *game);

void InitTileBarRects(Game *game);

void InitBoardRects(Game *game);

void InitializeGame(Game *game);

void LoadGameTextures(UserInterface*, SDL_Renderer*);

void LoadMenuTextures(UserInterface *ui, SDL_Renderer *ren);

void LoadGameTextures(UserInterface* ui, SDL_Renderer* ren);

void InitializeMenu(Game *game);