#include "../include/helper.h"
#include "../include/types.h"

Position GetMousePos(SDL_Event e) {
	Position p;
	p.x = e.button.x;
	p.y = e.button.y;
	return p;
}

void SelectBoardTile(Game *game, Position mousepos) {
	Position p;
	p.x = mousepos.x / 54;
	p.y = mousepos.y / 54;
	game->selectedBoardTile = p;
	// printf("%d .. %d ", game->selectedBoardTile.x, game->selectedBoardTile.y);
	return;
}


void PlaceTile(Game *game) {


	StagedTile *temp = malloc(sizeof(StagedTile));

	temp->tile  = game->selectedTile;
	temp->x_pos = game->selectedBoardTile.x;
	temp->y_pos = game->selectedBoardTile.y;

	game->ui.board.stagedTiles[game->ui.board.numStagedTiles] = temp;

	game->ui.board.numStagedTiles++;



	// printf("~~%d   \n", game->ui.board.numStagedTiles);
	fflush(stdout);

	// printf("TEST\n");
	return;

}