#include "../include/helper.h"
#include "../include/types.h"
#include "../include/hash.h"


void append(char *s, char c) {
    int len = strlen(s);
    s[len] = c;
    s[len+1] = "\0";
    return;
}

Position GetMousePos(SDL_Event e) {
	Position p;
	p.x = e.button.x;
	p.y = e.button.y;
	return p;
}

bool CheckClick(Position pos, SDL_Rect r) {
	if (pos.x < r.x) return false;
	else if (pos.y < r.y) return false;
	else if (pos.x > r.x + r.w) return false;
	else if (pos.y > r.y + r.h) return false;
	else return true;
}

void SelectBoardTile(Game *game, Position mousepos) {
	Position p;
	p.x = mousepos.x / 54;
	p.y = mousepos.y / 54;
	game->gameinfo.selectedBoardTile = p;
	// printf("%d .. %d ", game->selectedBoardTile.x, game->selectedBoardTile.y);
	return;
}

void PlaceTile(GameInfo *gameinfo, Board *b) {

	int x = gameinfo->selectedBoardTile.x;
	int y = gameinfo->selectedBoardTile.y;

	StagedTile *temp = malloc(sizeof(StagedTile));

	temp->tile  = gameinfo->selectedTile;
	temp->x_pos = x;
	temp->y_pos = y;

	b->stagedTiles[b->numStagedTiles] = temp;
	b->numStagedTiles++;
	b->boardTiles[x][y].stval = gameinfo->selectedTile;

	// printf("~~%d   \n", game->ui.board.numStagedTiles);
	// fflush(stdout);

	// printf("TEST\n");
	return;

}


bool CheckTilePlacement(StagedTile *st[], int *location, bool *wordDirection) {

	printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__ );

	if (st[0] == NULL) return -1;

	int x = 0; int y = 0;
	bool xflag = true;
	bool yflag = true;


	for (int i = 0; i < 7; i++) {
		if (st[i] == NULL) break;
		if (i == 0) {
			x = st[i]->x_pos;
			y = st[i]->y_pos;
		} else {
			if (st[x]->x_pos != x) xflag = false;
			if (st[x]->y_pos != y) yflag = false;
		}
	}


	printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__ );

	if (xflag) {
		location = x;
		wordDirection = VERTICAL;
		printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__ );
		return true;
	} else if (yflag) {
		location = y;
		wordDirection = HORIZONTAL;
		printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__ );
		return true;
	} else {
		location = -1;
		wordDirection = false;
		printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__ );
		return false;
	}

	printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__ );
	return false;
}

int findLow(StagedTile *st[], bool direction) {
	int low = 0;
	if (direction == VERTICAL) {
		low = st[0]->y_pos;
		for (int i = 0; i < 7; i ++) {
			if (st[i] == NULL) break;
			if (st[i]->y_pos < low) low = st[i]->y_pos;
		}
	} else {
		low = st[0]->x_pos;
		for (int i = 0; i < 7; i ++) {
			if (st[i] == NULL) break;
			if (st[i]->x_pos < low) low = st[i]->x_pos;
		}
	}
	return low;
}

int findHigh(StagedTile *st[], bool direction) {
	int high = 0;
	if (direction == VERTICAL) {
		high = st[0]->y_pos;
		for (int i = 0; i < 7; i ++) {
			if (st[i] == NULL) break;
			if (st[i]->y_pos > high) high = st[i]->y_pos;
		}
	} else {
		high = st[0]->x_pos;
		for (int i = 0; i < 7; i ++) {
			if (st[i] == NULL) break;
			if (st[i]->x_pos > high) high = st[i]->x_pos;
		}
	}
	return high;
}



int CheckConnection(Board *board, int x, int y, bool orientation) {


	// checking each letter for horizontal connections
	if (orientation == VERTICAL) {

		bool leftTile = board->boardTiles[x-1][y].occupied;
		bool rightTile = board->boardTiles[x+1][y].occupied;
	
		// checking both sides
		if (leftTile && rightTile) {
			return CT_INVALID;
		}
		// checking left
		else if (leftTile) {
			AdjacencyNode *head = board->boardTiles[x-1][y].adjList;
			// loop until either end of list or most recent horizontal word is found
			while (head->next != NULL || head->direction != HORIZONTAL) {
				head = head->next;
			}
			char *word[100];
			// horizontal word next to letter
			if (head->direction == HORIZONTAL) {
				strcpy(word, head->word);
				append(word, ALPHABET[board->boardTiles[x][y].stval]);
				if (validate(word)) return CT_VALID;
				else return CT_INVALID;
			// single letter next to letter
			} else {
				strcpy(word, ALPHABET[board->boardTiles[x-1][y].tile->letter]);
				strcat(word, ALPHABET[board->boardTiles[x][y].stval]);
				if (validate(word)) return CT_VALID;
				else return CT_INVALID;
			}
		
		//checking right
		} else if (rightTile) {
			AdjacencyNode *head = board->boardTiles[x+1][y].adjList;
			while (head->next != NULL || head->direction != HORIZONTAL) {
				head = head->next;
			}
			char *word[100];
			// horizontal word next to letter
			if (head->direction == HORIZONTAL) {
				strcpy(word, ALPHABET[board->boardTiles[x][y].stval]);
				strcat(word, head->word);
				if (validate(word)) return CT_VALID;
				else return CT_INVALID;
			} else {
				strcpy(word, ALPHABET[board->boardTiles[x][y].stval]);
				strcat(word, board->boardTiles[x+1][y].tile->letter);
				if (validate(word)) return CT_VALID;
				else return CT_INVALID;
			}

			return CT_NONE;
		}


	// checking each letter for VERTICAL connections
	} else {
		return CT_INVALID;


	}




	// // checking if connected above
	// if (board->boardTiles[x][y - 1].occupied == true) {
	// 	AdjacencyNode *head = board->boardTiles[x][y-1].adjList;
	// 	while (head->next != NULL || head->direction != HORIZONTAL) {
	// 		head = head->next;
	// 	}
	// 	char *word[100];
	// 	if (head->direction == HORIZONTAL) {
	// 		strcpy(word, head->word);
	// 		append(word, ALPHABET[board->boardTiles[x][y].stval]);
	// 		if (validate(word)) return true;
	// 		else return false;
	// 	} else {
	// 		strcpy(word, board->boardTiles[x][y-1])
	// 		append(word, board->boardTiles[x][y].tile.letter);
	// 		if (validate(word)) return true;
	// 		else return false;
	// 	}

	// // checking if connected below
	// } else if (board->boardTiles[x][y + 1].occupied == true) {
	// 	AdjacencyNode *head = board->boardTiles[x][y+1].adjList;
	// 	while (head->next != NULL || head->direction != HORIZONTAL) {
	// 		head = head->next;
	// 	}
	// 	char *word[100];
	// 	if (head->direction == HORIZONTAL) {
	// 		strcpy(word, ALPHABET[board->boardTiles[x][x].stval]);
	// 		strcat(word, head->word);
	// 		if (validate(word)) return true;
	// 		else return false;
	// 	} else {
	// 		append(word, board->boardTiles[x][y - 1].tile.letter);
	// 		if (validate(word)) return true;
	// 		else return false;
	// 	}
	
	// //checking if connected to the left
	// } else if (board->boardTiles[x - 1][y].occupied == true) {

	// // checking if connected to the right	
	// } else if (board->boardTiles[x + 1][y].occupied == true) {

	// } else {
	// 	return false;
	// }
}

void Lock(Board *board, StagedTile *st, Tile *letters) {
	int x = st->x_pos;
	int y = st->y_pos;

	board->boardTiles[x][y].occupied = true;
	board->boardTiles[x][y].selected = false;
	board->boardTiles[x][y].tile = &letters[st->tile];

}

void SubmitWord(UserInterface *ui) {
	Board *board = &ui->board;
	// StagedTile *st[] = board->stagedTiles;
	int location; bool direction;
	char *word[100];

	// direction = true means vertical placement
	// direction = false means horizontal placement

	bool validPlacement = CheckTilePlacement(&board->stagedTiles, &location, &direction);	

	bool oneConnectionMinimum = false;

	if (validPlacement) {

		if (direction == VERTICAL) {
			int low = findLow(&board->stagedTiles, VERTICAL);
			int high = findHigh(&board->stagedTiles, VERTICAL);
			for (int i = low; i <= high; i ++) {
				int r = CheckConnection(board, location, i, VERTICAL);
				if (r == CT_VALID) oneConnectionMinimum = true;
				else if (r == CT_INVALID) break;
				else {
					strcat(word, ALPHABET[board->boardTiles[location][i].stval]);
				}
			}

			if (oneConnectionMinimum) {
				if (validate(word)) {
					for (int i = 0; i < 7; i ++){
						if (board->stagedTiles[i] == NULL) break;
						else Lock(board, board->stagedTiles[i], ui->letters);
					}
				}
			}

		} else if (direction == HORIZONTAL) {
			// int low = findLow(st, HORIZONTAL);
			// int high = findHigh(st, HORIZONTAL);

		}

	}

}




// check move() pseudocode

// 1. determine if word is connected
// 		if no, reject word
//		check if connection is valid (validate word)
//			if no, reject word
// 2. check if all points of connection are valid
//		for all lets, if no, reject word
// 3. determine if main word is valid
// 		if no, reject word
// 4. done return valid/true