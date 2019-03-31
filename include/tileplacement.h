#pragma once
#include "types.h"

void SelectBoardTile(Game *game, Position mousepos);

void PlaceTile(GameInfo*, Board*);

bool CheckTilePlacement(StagedTile *st[], int *location, bool *wordDirection);

void CreateTempAdjacency(int, int, bool, char *, Board*);

int CheckConnection(Board *board, int x, int y, bool orientation, int *moveScore);

void Lock(Board*, StagedTile*, Tile*);

void freeList(AdjacencyNode*);

void printAdjacencyLists(Board*);

void LockAdjacencies(Board*);

bool SubmitWord(UserInterface *ui);

void RefillTiles(TileBar *tb);

void RejectMove();

void printTempAdjList(Board *board);