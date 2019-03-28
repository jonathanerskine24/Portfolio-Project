#include "types.h"


// reorder some stuff into other files... kinda disorganized atm
// also comment code here

Position GetMousePos(SDL_Event e);

void SelectBoardTile(Game *game, Position mousepos);

void PlaceTile(GameInfo*, Board*);

int CheckConnection(Board *board, int x, int y, bool orientation);

void SubmitWord(UserInterface *ui);

bool CheckWord();

void LockBoard();

bool CheckTilePlacement(StagedTile *st[], int *location, bool *wordDirection);

int findLow(StagedTile *st[], bool direction);

int findHigh(StagedTile* st[], bool direction);

void append(char *s, char c);

void RejectMove();