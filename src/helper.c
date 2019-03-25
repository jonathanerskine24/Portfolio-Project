#include "../include/helper.h"
#include "../include/types.h"
#include "../include/hash.h"

int ConvertXYtoIndex(int x, int y) {
	return ((y * BOARD_SIZE) + (x));
	// printf("%d and %d maps to %d\n", x, y, z);
	// return z;
}

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
		printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__ );		
		*location = y;
		printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__ );
		*wordDirection = HORIZONTAL;
		printf("Direction = %d Location = %d \n", *wordDirection, *location);
		printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__ );

		return true;
	} else {
		*location = -1;
		*wordDirection = false;
		printf("Direction = %d Location = %d \n", *wordDirection, *location);
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

void CreateTempAdjacency(int s, int e, bool orientation, char *w, Board *board) {
	printf("\n---- CREATING ADJACENCY NODE ----\n");
	printf("Word: %s START: %d END: %d ", w, s, e);
	if (orientation == VERTICAL) printf("ORIENTATION: VERTICAL\n");
	else if (orientation == HORIZONTAL) printf("ORIENTATION: HORIZONTAL\n");
	printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
	AdjacencyNode *temp = malloc(sizeof(AdjacencyNode));
	printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
	temp->start = s;
	printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
	temp->end = e;
	temp->direction = orientation;
	printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
	strcpy(temp->word, w);
	printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
	temp->next = board->tempAdjacencies;
	printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
	board->tempAdjacencies = temp;
	printf("%s starts at %d and ends at %d and is %d", temp->word, temp->start, temp->end, temp->direction);
	return;
}

// TODO: 
// FOR VERTICAL WORDS: CHECK TOP AND BOTTOM OF FIRST AND LAST LETTERS FOR LETTERS OR WORDS
// FOR HORIZONTAL WORDS: CHECK LEFT AND RIGHT OF FIRST AND LAST LETTERS FOR LETERS OR WORDS


int CheckConnection(Board *board, int x, int y, bool orientation) {

	char *word[100];
	word[0] = '\0';

	// checking each letter for horizontal connections
	if (orientation == VERTICAL) {

		bool leftTile = board->boardTiles[x-1][y].occupied;
		bool rightTile = board->boardTiles[x+1][y].occupied;
	
		// if tile is on center tile
		if (x == board->center && y == board->center) {
			printf("\nCENTER: %d\n", board->center);
			printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
			return CT_VALID;
		}


		// checking both sides
		if (leftTile && rightTile) {

			printf("LEFT AND RIGHT DETECTED!\n");

			AdjacencyNode *L_head = board->boardTiles[x-1][y].adjList;
			AdjacencyNode *R_head = board->boardTiles[x+1][y].adjList;

			if (L_head != NULL) {
				printf("WORD FOUND TO THE LEFT!\n");
				// loop until either end of list or most recent horizontal word is found
				while (L_head->next != NULL && L_head->direction != HORIZONTAL) {
					L_head = L_head->next;
				}
				// if there is a horizontal word, must copy that word and append letter
				if (L_head->direction == HORIZONTAL) {
					strcpy(word, L_head->word);
					append(word, ALPHABET[board->boardTiles[x][y].stval]);
					// if (validate(word)) {
					// 	printf("new word: %s\n", word);
					// 	CreateTempAdjacency(head->start, head->end + 1, HORIZONTAL, word, board);
					// 	return CT_VALID;
					// }
					// else return CT_INVALID;
				} 
			} else {
				append(word, board->boardTiles[x-1][y].tile->letter);
				append(word, ALPHABET[board->boardTiles[x][y].stval]);
			}

			if (R_head != NULL) {
				printf("WORD FOUND TO THE RIGHT!\n");
				while (R_head->next != NULL && R_head->direction != HORIZONTAL) {
					printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
					R_head = R_head->next;
					printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
				}
				if (R_head->direction == HORIZONTAL) {					
					// append(word, ALPHABET[board->boardTiles[x][y].stval]);
					strcat(word, R_head->word);
					// if (validate(word)) {
					// 	printf("new word: %s\n", word);
					// 	CreateTempAdjacency(head->start-1, head->end, HORIZONTAL, word, board);
					// 	return CT_VALID;
					// }
					// else return CT_INVALID;
				}
			} else {
				// append(word, ALPHABET[board->boardTiles[x][y].stval]);
				// printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
				append(word, board->boardTiles[x+1][y].tile->letter);
			}

			if (validate(word)) {
				printf("new word: %s\n", word);
				CreateTempAdjacency(L_head->start, R_head->end, HORIZONTAL, word, board);
				return CT_VALID;
			}
			else return CT_INVALID;

		}

		// checking left
		else if (leftTile) {
			printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
			AdjacencyNode *head = board->boardTiles[x-1][y].adjList;
			printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);

			// if there is a word placed there
			if (head != NULL) {
				printf("WORD FOUND TO THE LEFT!\n");
				// loop until either end of list or most recent horizontal word is found
				while (head->next != NULL && head->direction != HORIZONTAL) {
					head = head->next;
				}
				// if there is a horizontal word, must copy that word and append letter
				if (head->direction == HORIZONTAL) {
					strcpy(word, head->word);
					append(word, ALPHABET[board->boardTiles[x][y].stval]);
					if (validate(word)) {
						printf("new word: %s\n", word);
						CreateTempAdjacency(head->start, head->end + 1, HORIZONTAL, word, board);
						return CT_VALID;
					}
					else return CT_INVALID;
				} 
			}
	
			// otherwise just a single letter
			append(word, board->boardTiles[x-1][y].tile->letter);
			append(word, ALPHABET[board->boardTiles[x][y].stval]);
			printf("~%s\n", word);
			if (validate(word)) {
				printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
				fflush(stdout);
				// int loc = ((y * BOARD_SIZE) + (x-1));
				int loc = ConvertXYtoIndex(x, y);
				printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
				CreateTempAdjacency(loc-1, loc, HORIZONTAL, word, board);
				return CT_VALID;
			}
			else return CT_INVALID;
		

		//checking right
		} else if (rightTile) {
			printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
			AdjacencyNode *head = board->boardTiles[x+1][y].adjList;
			printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);

			// if there is a word to the right
			if (head != NULL) {
				printf("WORD FOUND TO THE RIGHT!\n");
				while (head->next != NULL && head->direction != HORIZONTAL) {
					printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
					head = head->next;
					printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
				}
				if (head->direction == HORIZONTAL) {					
					append(word, ALPHABET[board->boardTiles[x][y].stval]);
					strcat(word, head->word);
					if (validate(word)) {
						printf("new word: %s\n", word);
						CreateTempAdjacency(head->start-1, head->end, HORIZONTAL, word, board);
						return CT_VALID;
					}
					else return CT_INVALID;
				}
			}

			printf("NO WORD TO RIGHT, but LETTER!\n");
			printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
			append(word, ALPHABET[board->boardTiles[x][y].stval]);
			printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
			append(word, board->boardTiles[x+1][y].tile->letter);
			printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
			printf("!%s\n", word);
			if (validate(word))  {
				int loc = ConvertXYtoIndex(x, y);
				printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
				CreateTempAdjacency(loc, loc+1, HORIZONTAL, word, board);
				return CT_VALID;
			}
			else return CT_INVALID;
		}

		return CT_NONE;

	// checking each letter for VERTICAL connections
	} else {

		printf("~~~CHECKING FOR VERTICAL CONNECTIONS~~~\n");

		bool topTile = board->boardTiles[x][y-1].occupied;
		bool bottomTile = board->boardTiles[x][y+1].occupied;		

		// check if tile is on the center of the board
		if (x == board->center && y == board->center) {
			printf("\nCENTER: %d\n", board->center);
			printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
			return CT_VALID;
		}

		// check top and bottom

		if (topTile && bottomTile) {
			return CT_INVALID;
		}

		//check top
		else if (topTile) {
			printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
			AdjacencyNode *head = board->boardTiles[x][y-1].adjList;
			printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);

			// if there is a word placed there
			if (head != NULL) {
				printf("WORD FOUND TO THE TOP!\n");
				// loop until either end of list or most recent horizontal word is found
				while (head->next != NULL && head->direction != VERTICAL) {
					head = head->next;
				}
				// if there is a horizontal word, must copy that word and append letter
				printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);	
				if (head->direction == VERTICAL) {
					printf("Found vertical word above...%s\n", head->word);
					strcpy(word, head->word);
					append(word, ALPHABET[board->boardTiles[x][y].stval]);
					if (validate(word)) {
						printf("new word: %s\n", word);
						CreateTempAdjacency(head->start, head->end + BOARD_SIZE, VERTICAL, word, board);
						return CT_VALID;
					}
					else return CT_INVALID;
				} 
			}
	
			// otherwise just a single letter
			append(word, board->boardTiles[x][y-1].tile->letter);
			append(word, ALPHABET[board->boardTiles[x][y].stval]);
			printf("~%s\n", word);
			if (validate(word)) {
				printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
				fflush(stdout);
				// int loc = ((y * BOARD_SIZE) + (x-1));
				int loc = ConvertXYtoIndex(x, y);
				printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
				CreateTempAdjacency(loc - BOARD_SIZE, loc, VERTICAL, word, board);
				return CT_VALID;
			}
			else return CT_INVALID;
		
		//checking right

		} else if (bottomTile) {
			// printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
			AdjacencyNode *head = board->boardTiles[x][y+1].adjList;
			// printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);

			// if there is a word to the right
			if (head != NULL) {
				printf("WORD FOUND TO THE RIGHT!\n");
				while (head->next != NULL && head->direction != VERTICAL) {
					printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
					head = head->next;
					printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
				}
				if (head->direction == VERTICAL) {					
					append(word, ALPHABET[board->boardTiles[x][y].stval]);
					strcat(word, head->word);
					if (validate(word)) {
						printf("new word: %s\n", word);
						CreateTempAdjacency(head->start - BOARD_SIZE, head->end, VERTICAL, word, board);
						return CT_VALID;
					}
					else return CT_INVALID;
				}
			}

			printf("NO WORD TO RIGHT, but LETTER!\n");
			printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
			append(word, ALPHABET[board->boardTiles[x][y].stval]);
			printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
			append(word, board->boardTiles[x][y+1].tile->letter);
			printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
			printf("!%s\n", word);
			if (validate(word))  {
				int loc = ConvertXYtoIndex(x, y);
				printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
				CreateTempAdjacency(loc, loc + BOARD_SIZE, VERTICAL, word, board);
				return CT_VALID;
			}
			else return CT_INVALID;
		}		

		return CT_NONE;

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

void freeList(AdjacencyNode* head) {
   AdjacencyNode *tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }

}

void printAdjacencyLists(Board *board) {
	for (int i = 0; i < 15; i ++){
		for (int j = 0; j <15; j++) {
			AdjacencyNode *tmp = board->boardTiles[i][j].adjList;
			while (tmp != NULL) {
				printf("%d is adjacent to %d and it spells %s", tmp->start, tmp->end, tmp->word);
				if (tmp->direction == HORIZONTAL) printf(" horizontally\n");
				else if (tmp->direction == VERTICAL) printf(" vertically\n"); 
				tmp = tmp->next;
			}
			// if (tmp == NULL) printf("%d %d has no adjacencies\n", i, j);
			// else {
			// }
		}
	}
}

void LockAdjacencies(Board *board) {
	printf("\n~~~LOCKING ADJACENCY NODES~~~\n");
	if (board->tempAdjacencies == NULL) return;
	printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
	AdjacencyNode *h = board->tempAdjacencies;
	printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
	while (h != NULL) {
		AdjacencyNode *temp1 = malloc(sizeof(AdjacencyNode));
		int x1 = h->start % BOARD_SIZE;
		int y1 = h->start / BOARD_SIZE;
		temp1->start = h->start;
		temp1->end = h->end;
		temp1->direction = h->direction;
		strcpy(temp1->word, h->word);
		temp1->next = board->boardTiles[x1][y1].adjList;
		board->boardTiles[x1][y1].adjList = temp1;

		AdjacencyNode *temp2 = malloc(sizeof(AdjacencyNode));
		int x2 = h->end % BOARD_SIZE;
		int y2 = h->end / BOARD_SIZE;
		temp2->start = h->start;
		temp2->end = h->end;
		temp2->direction = h->direction;
		strcpy(temp2->word, h->word);
		temp1->next = board->boardTiles[x2][y2].adjList;
		board->boardTiles[x2][y2].adjList = temp2;

		h = h->next;
	}

	printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
	freeList(board->tempAdjacencies);
	printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
	board->tempAdjacencies = NULL;
	return;
}

void SubmitWord(UserInterface *ui) {
	Board *board = &ui->board;
	int location; bool direction;
	char *word[100];
	word[0] = '\0';
	bool validPlacement = CheckTilePlacement(&board->stagedTiles, &location, &direction);	
	bool oneConnectionMinimum = false;
	printf("Direction = %d Location = %d \n", direction, location);

	if (validPlacement) {

		if (direction == VERTICAL) {
			int low = findLow(&board->stagedTiles, VERTICAL);
			int high = findHigh(&board->stagedTiles, VERTICAL);
			// check each tile and react accordingly...
			for (int i = low; i <= high; i ++) {
				int r = CheckConnection(board, location, i, VERTICAL);
				if (r == CT_VALID) {
					append(word, ALPHABET[board->boardTiles[location][i].stval]);
					oneConnectionMinimum = true;
				}
				else if (r == CT_INVALID) {
					printf("INVALID\n");
					break;
				}
				else { 
					printf("%d\n", board->boardTiles[location][i].stval);
					printf("%c\n", ALPHABET[board->boardTiles[location][i].stval]);
					append(word, ALPHABET[board->boardTiles[location][i].stval]);
					printf("%s\n", word);
				}
			}

			if (oneConnectionMinimum) {
				printf("%s\n", word);
				fflush(stdout);
				if (validate(word)) {
					printf("VALID WORD!\n");
					for (int i = 0; i < 7; i ++){
						if (board->stagedTiles[i] == NULL) break; 
						Lock(board, board->stagedTiles[i], ui->letters);
						board->stagedTiles[i] = NULL;
					}
					if (board->stagedTiles[0] != NULL) printf("Didn't clear staged tiles\n");
					printf("Creating adjacency %s between %d and %d", word, low, high);
					CreateTempAdjacency(ConvertXYtoIndex(location, low), ConvertXYtoIndex(location, high), VERTICAL, word, board);
					LockAdjacencies(board);
					printAdjacencyLists(board);
				}
			}

		} else if (direction == HORIZONTAL) {
			int low = findLow(&board->stagedTiles, HORIZONTAL);
			int high = findHigh(&board->stagedTiles, HORIZONTAL);

			// check each tile and react accordingly
			for (int i = low; i <= high; i++) {
				int r = CheckConnection(board, i, location, HORIZONTAL);
				if (r == CT_VALID) {
					append(word, ALPHABET[board->boardTiles[i][location].stval]);
					oneConnectionMinimum = true;
				} else if (r == CT_INVALID) {
					printf("INVALID\n");
					break;
				} else {
					printf("%d\n", board->boardTiles[i][location].stval);
					printf("%c\n", ALPHABET[board->boardTiles[i][location].stval]);
					append(word, ALPHABET[board->boardTiles[i][location].stval]);
					printf("%s\n", word);
				}
			}

			if (oneConnectionMinimum) {
				printf("ONE CONNECTION MINIMUM!\n");
				printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
				printf("%s\n", word);
				fflush(stdout);
				if (validate(word)) {
					printf("VALID WORD!\n");
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
					// int loc = ConvertXYtoIndex(location, low);
					// int loc2 = ConvertXYtoIndex(location, high);
					printf("loc = %d low = %d high = %d\n", location, low, high);
					printf("Creating adjacency %s between %d and %d", word, low, high);
					CreateTempAdjacency(ConvertXYtoIndex(low, location), ConvertXYtoIndex(high, location), HORIZONTAL, word, board);
					LockAdjacencies(board);
					printAdjacencyLists(board);
				} else {
					printf("~~%s is not a valid word\n", word);
				}
			}




		}

	}

}