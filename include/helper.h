#include "types.h"


Position GetMousePos(SDL_Event e);

void SelectBoardTile(Game *game, Position mousepos);

// void PlaceTile(Game *game);

void PlaceTile(GameInfo*, Board*);

int CheckConnection(Board *board, int x, int y, bool orientation);

void SubmitWord(UserInterface *ui);

char* EstablishWord();

bool CheckWord();

void LockBoard();

bool CheckTilePlacement(StagedTile *st[], int *location, bool *wordDirection);

int findLow(StagedTile *st[], bool direction);

int findHigh(StagedTile* st[], bool direction);

void append(char *s, char c);

// need to make a function for after determining word is one line that
// checks to see if any letters already on the board are to be incorporated
// into the word