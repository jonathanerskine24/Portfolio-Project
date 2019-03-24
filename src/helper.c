#include "../include/helper.h"
#include "../include/types.h"
#include "../include/hash.h"


void append(char *s, char c) {
    int len = strlen(s);
    s[len] = c;
    s[len+1] = '\0';
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

		printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__ );
		if (st[i] == NULL) break;

		printf("FILE: %s, FUNCTION: %s, LINE: %d ITERATION: %d\n", __FILE__, __func__, __LINE__, i);

		if (i == 0) {
			printf("FILE: %s, FUNCTION: %s, LINE: %d ITERATION: %d\n", __FILE__, __func__, __LINE__, i);
			x = st[i]->x_pos;
			y = st[i]->y_pos;
		} else {
			printf("FILE: %s, FUNCTION: %s, LINE: %d ITERATION: %d\n", __FILE__, __func__, __LINE__, i);
			if (st[i]->x_pos != x) {
				printf("x: %d not equal to %d", st[i]->x_pos, x);
				printf("FILE: %s, FUNCTION: %s, LINE: %d ITERATION: %d\n,", __FILE__, __func__, __LINE__, i);
				xflag = false;
			}
			if (st[i]->y_pos != y) {
				printf("Y: %d not equal to %d", st[i]->y_pos, y);
				printf("FILE: %s, FUNCTION: %s, LINE: %d ITERATION: %d\n,", __FILE__, __func__, __LINE__, i);
				yflag = false;
			}
			printf("FILE: %s, FUNCTION: %s, LINE: %d ITERATION: %d\n", __FILE__, __func__, __LINE__, i);
			
		}
	}


	printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__ );

	if (xflag) {
		*location = x;
		*wordDirection = VERTICAL;
		printf("Direction = %d Location = %d \n", *wordDirection, *location);
		printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__ );
		return true;
	} else if (yflag) {
		*location = y;
		*wordDirection = HORIZONTAL;
		printf("Direction = %d Location = %d \n", wordDirection, location);
		printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__ );
		return true;
	} else {
		*location = -1;
		*wordDirection = false;
		printf("Direction = %d Location = %d \n", wordDirection, location);
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
	
		if (x == board->center && y == board->center) {
			return CT_VALID;
		}


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

}

void Lock(Board *board, StagedTile *st, Tile *letters) {
	int x = st->x_pos;
	int y = st->y_pos;

	board->boardTiles[x][y].occupied = true;
	board->boardTiles[x][y].selected = false;
	board->boardTiles[x][y].tile = &letters[st->tile];
	board->numStagedTiles--;
}

void SubmitWord(UserInterface *ui) {
	Board *board = &ui->board;
	// StagedTile *st[] = board->stagedTiles;
	int location; bool direction;
	char *word[100];
	word[0] = '\0';
	// direction = true means vertical placement
	// direction = false means horizontal placement

	bool validPlacement = CheckTilePlacement(&board->stagedTiles, &location, &direction);	

	printf("Direction = %d Location = %d \n", direction, location);

	bool oneConnectionMinimum = false;

	//	NOTE
	//	SEEMS TO WORK FOR PLACING THE FIRST WORD VERTICALLY
	//	HORIZONTAL NOT DONE
	//	ADDING SECOND VERTICAL WORD DOESNT WORK
	//	THINK IT HAS SOMETHING TO DO WITH FIRST CHECK CONNECTION

	if (validPlacement) {

		if (direction == VERTICAL) {
			printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
			int low = findLow(&board->stagedTiles, VERTICAL);
			printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
			int high = findHigh(&board->stagedTiles, VERTICAL);
			printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
			for (int i = low; i <= high; i ++) {
				printf("FILE: %s, FUNCTION: %s, LINE: %d ITERATION: %d\n", __FILE__, __func__, __LINE__, i - low);
				int r = CheckConnection(board, location, i, VERTICAL);
				printf("FILE: %s, FUNCTION: %s, LINE: %d ITERATION: %d\n", __FILE__, __func__, __LINE__, i - low);
				if (r == CT_VALID) {
					printf("FILE: %s, FUNCTION: %s, LINE: %d ITERATION: %d\n", __FILE__, __func__, __LINE__, i - low);
					printf("Location: %d i: %d\n", location, i);
					printf("%d\n", board->boardTiles[location][i].stval);
					printf("%c\n", ALPHABET[board->boardTiles[location][i].stval]);
					append(word, ALPHABET[board->boardTiles[location][i].stval]);
					oneConnectionMinimum = true;
				}
				else if (r == CT_INVALID) {
					printf("FILE: %s, FUNCTION: %s, LINE: %d ITERATION: %d\n", __FILE__, __func__, __LINE__, i - low);
					printf("INVALID\n");
					break;
				}
				else { 
					printf("FILE: %s, FUNCTION: %s, LINE: %d ITERATION: %d\n", __FILE__, __func__, __LINE__, i - low);
					printf("Location: %d i: %d\n", location, i);
					printf("%d\n", board->boardTiles[location][i].stval);
					printf("%c\n", ALPHABET[board->boardTiles[location][i].stval]);
					append(word, ALPHABET[board->boardTiles[location][i].stval]);
					printf("%s\n", word);
				}
			}

			printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
			if (oneConnectionMinimum) {
				printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
				printf("%s\n", word);
				fflush(stdout);
				if (validate(word)) {
					printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
					for (int i = 0; i < 7; i ++){
						if (board->stagedTiles[i] == NULL) break; 
						printf("FILE: %s, FUNCTION: %s, LINE: %d, ITERATION: %d\n", __FILE__, __func__, __LINE__, i);
						Lock(board, board->stagedTiles[i], ui->letters);
						board->stagedTiles[i] = NULL;
					}
					printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
					if (board->stagedTiles[0] != NULL) printf("Didn't clear staged tiles\n");
					printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
				}
			}

		} else if (direction == HORIZONTAL) {
			printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);

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