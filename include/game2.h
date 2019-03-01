#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "types.h"



void Init(Game* game, const char* title, int xpos, int ypos, int width, int height, bool fullScreen);

void HandleEvents(Game *game);

void Update(Game *game);

void Render(Game *game);

void Clean(Game *game);

// put this shit somewhere else

void checkPlayerTileClick(Position mousePos, Tile *location);