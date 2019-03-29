#include "types.h"

int ConvertXYtoIndex(int x, int y);

void append(char *s, char c);

Position GetMousePos(SDL_Event e);

bool CheckClick(Position pos, SDL_Rect r);

int findLow(StagedTile *st[], bool direction);

int findHigh(StagedTile* st[], bool direction);
