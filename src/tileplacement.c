#include "../include/tileplacement.h"
#include "../include/helper.h"
#include "../include/scoring.h"

void SelectBoardTile(Game *game, Position mousepos) {
	Position p;
	p.x = mousepos.x / game->gameinfo.params.TILE_SIZE;
	p.y = mousepos.y / game->gameinfo.params.TILE_SIZE;
	game->gameinfo.selectedBoardTile = p;
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



	return;

}

bool CheckTilePlacement(StagedTile *st[], int *location, bool *wordDirection) {

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
			if (st[i]->x_pos != x) {

				xflag = false;
			}
			if (st[i]->y_pos != y) {


				yflag = false;
			}
		}
	}

	if (xflag) {
		*location = x;
		*wordDirection = VERTICAL;
		return true;
	} else if (yflag) {
		*location = y;
		*wordDirection = HORIZONTAL;
		return true;
	} else {
		*location = -1;
		*wordDirection = false;
		return false;
	}
	return false;
}

void SwapTiles(TileBar *tb){
	for (int i = 0; i < 7; i++) {
		int tileToReturn = tb->playerTiles[i].val;
		tileBag[tileToReturn++];
	}
	for (int i = 0; i < 7; i++) {
		tb->playerTiles[i].val = SelectTile();
	}
	return;
}

void CreateTempAdjacency(int s, int e, bool orientation, char *w, Board *board) {
	AdjacencyNode *temp = malloc(sizeof(AdjacencyNode));
	temp->start = s;
	temp->end = e;
	temp->direction = orientation;
	strcpy(temp->word, w);
	temp->next = board->tempAdjacencies;
	board->tempAdjacencies = temp;

	return;
}

int CheckConnection(Board *board, int x, int y, bool orientation, int *moveScore) {
	char *word[100];
	word[0] = '\0';


	if (x > MAXIMUM_INDEX || y > MAXIMUM_INDEX) {
		return CT_INVALID;
	}

	if (board->boardTiles[x][y].occupied == true) return CT_INVALID;



	// PrintBoard(board);

	int tileLoc = ConvertXYtoIndex(x, y); // i am stupid

	// checking for HORIZONTAL adjacencies along each tile
	if (orientation == VERTICAL) {

		bool leftTile;
		bool rightTile;



		// check whether there exists a left or a right tile for the current tile
		if (x != 0) leftTile = board->boardTiles[x-1][y].occupied;
		else leftTile = false;
		if (x != MAXIMUM_INDEX) rightTile = board->boardTiles[x+1][y].occupied;
		else rightTile = false;


		// PrintBoard(board);

		// if tile is on center tile
		if (x == board->center && y == board->center) {
			// printf("\nCENTER: %d\n", board->center);
			// printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
			append(word, ALPHABET[board->boardTiles[x][y].stval]);
			CreateTempAdjacency(tileLoc, tileLoc, HORIZONTAL, word, board);
			return CT_VALID;
		}

		// printf("CHECK CONNECTION LINE: %d\n", __LINE__);


		// if left and right tile
		if (leftTile && rightTile) {




			strcpy(word,board->boardTiles[x-1][y].HorizontalAdjacency->word);
		
			append(word, ALPHABET[board->boardTiles[x][y].stval]);
		
			strcat(word, board->boardTiles[x+1][y].HorizontalAdjacency->word);
			if (validate(word)) {

				CreateTempAdjacency(board->boardTiles[x-1][y].HorizontalAdjacency->start, board->boardTiles[x+1][y].HorizontalAdjacency->end, HORIZONTAL, word, board);
                *moveScore += CalculateScore(word);
				return CT_VALID;
			} else {
				return CT_INVALID;
			}
		} 

		// if left tile only
		else if (leftTile) {
			
			


			strcpy(word, board->boardTiles[x-1][y].HorizontalAdjacency->word);
			append(word, ALPHABET[board->boardTiles[x][y].stval]);
			if (validate(word)) {
				CreateTempAdjacency(board->boardTiles[x-1][y].HorizontalAdjacency->start, tileLoc, HORIZONTAL, word, board);
                *moveScore += CalculateScore(word);
				return CT_VALID;
			} else {

				return CT_INVALID;
			}
		}


		// if right tile only
		else if (rightTile) {
			
			append(word, ALPHABET[board->boardTiles[x][y].stval]);
			strcat(word, board->boardTiles[x+1][y].HorizontalAdjacency->word);
			if (validate(word)) {
				CreateTempAdjacency(tileLoc, board->boardTiles[x+1][y].HorizontalAdjacency->end, HORIZONTAL, word, board);
                *moveScore += CalculateScore(word);
				return CT_VALID;
			} else {

				return CT_INVALID;
			}
		}


		// not connected on the left or right
		append(word, ALPHABET[board->boardTiles[x][y].stval]);
		CreateTempAdjacency(tileLoc, tileLoc, HORIZONTAL, word, board);
		return CT_NONE;
	}

	// checking for VERTICAL adjacencies along each tile
	else {

		bool topTile;
		bool bottomTile;

		// check whether there exists a left or a right tile for the current tile
		if (y != 0) topTile = board->boardTiles[x][y-1].occupied;
		else topTile = false;
		if (y != MAXIMUM_INDEX) bottomTile = board->boardTiles[x][y+1].occupied;
		else bottomTile = false;		



		// check if on center tile
		if (x == board->center && y == board->center) {
			append(word, ALPHABET[board->boardTiles[x][y].stval]);
			CreateTempAdjacency(tileLoc, tileLoc, VERTICAL, word, board);
			return CT_VALID;
		}

		// check for top and bottom tile
		if (topTile && bottomTile) {



			strcpy(word,board->boardTiles[x][y-1].VerticalAdjacency->word);
			append(word, ALPHABET[board->boardTiles[x][y].stval]);
			strcat(word, board->boardTiles[x][y+1].VerticalAdjacency->word);
			if (validate(word)) {
				CreateTempAdjacency(board->boardTiles[x][y-1].VerticalAdjacency->start, board->boardTiles[x][y+1].VerticalAdjacency->end, VERTICAL, word, board);
	
				*moveScore += CalculateScore(word);
				return CT_VALID;
			} else {

				return CT_INVALID;
			}
		} 

		// check for top tile only
		else if (topTile) {

			


			strcpy(word, board->boardTiles[x][y-1].VerticalAdjacency->word);
			append(word, ALPHABET[board->boardTiles[x][y].stval]);
			if (validate(word)) {
				CreateTempAdjacency(board->boardTiles[x][y-1].VerticalAdjacency->start, tileLoc, VERTICAL, word, board);
                *moveScore += CalculateScore(word);
				return CT_VALID;
			} else {

				return CT_INVALID;
			}
		}

		// check for bottom tile only
		else if (bottomTile) {

			append(word, ALPHABET[board->boardTiles[x][y].stval]);
			strcat(word, board->boardTiles[x][y+1].VerticalAdjacency->word);
			if (validate(word)) {
				CreateTempAdjacency(tileLoc, board->boardTiles[x][y+1].VerticalAdjacency->end, VERTICAL, word, board);

                *moveScore += CalculateScore(word);
				return CT_VALID;
			} else {

				return CT_INVALID;
			}
		}

		// not connected on the TOP or bottom
		append(word, ALPHABET[board->boardTiles[x][y].stval]);
		CreateTempAdjacency(tileLoc, tileLoc, VERTICAL, word, board);
		return CT_NONE;
	}


}

void Lock(Board *board, StagedTile *st, Tile *boardTiles) {
	int x = st->x_pos;
	int y = st->y_pos;

	board->boardTiles[x][y].occupied = true;
	board->boardTiles[x][y].selected = false;
	board->boardTiles[x][y].tile = &boardTiles[st->tile];
	board->numStagedTiles--;
}

void LockAI(Board *board, StagedTile *st, Tile *boardTiles) {
	int x = st->x_pos;
	int y = st->y_pos;
	board->boardTiles[x][y].occupied = true;
	board->boardTiles[x][y].selected = false;
	board->boardTiles[x][y].tile = &boardTiles[st->tile];
	board->numAIstagedTiles--;
	return;
}

void RejectMove(UserInterface* ui, TileBar *tb) {

	Board *board = &ui->board;
	int n = board->numStagedTiles;

	// clear up staged tiles
	for (int i = 0; i < n; i ++) {
		int x = board->stagedTiles[i]->x_pos;
		int y = board->stagedTiles[i]->y_pos;
		board->boardTiles[x][y].stval = -1;
		free(board->stagedTiles[i]);
		board->stagedTiles[i] = NULL;
		board->numStagedTiles--;
	}
	
	// set placed tiles back to no longer placed
	for (int i = 0; i < 7; i ++) {
		if (tb->playerTiles[i].placed == true) {
			tb->playerTiles[i].placed = false;
		}
	}

	freeList(board->tempAdjacencies);
	board->tempAdjacencies = NULL;

	// printAdjacencyLists(&ui->board);

	return;
}

void RejectAIMove(UserInterface *ui) {



	Board *board = &ui->board;
	int n = board->numAIstagedTiles;

	for (int i = 0; i < n; i ++) {
		int x = board->AIstagedTiles[i]->x_pos;
		int y = board->AIstagedTiles[i]->y_pos;
		board->boardTiles[x][y].stval = -1;
		free(board->AIstagedTiles[i]);
		board->AIstagedTiles[i] = NULL;
		board->numAIstagedTiles--;
	}

	freeList(board->tempAdjacencies);
	board->tempAdjacencies = NULL;

	// printAdjacencyLists(&ui->board);
	return;
}

void freeList(AdjacencyNode* head) {
   AdjacencyNode *temp;

   while (head != NULL) {
       temp = head;
       head = head->next;
       free(temp);
    }

}

void printAdjacencyLists(Board *board) {

	AdjacencyNode *head = board->adjacencyListHead;

	printf("Adj List~~\n");
	while (head != NULL) {
		if(head->direction == VERTICAL) printf("Vertical --- ");
		else printf("Horizontal - ");
		printf("%s between %d and %d\n", head->word, head->start, head->end);
		head = head->next;
	}

	printf("\nAdj on Tiles\n");
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {

			if (board->boardTiles[j][i].VerticalAdjacency != NULL) {
				AdjacencyNode *t = board->boardTiles[j][i].VerticalAdjacency;
				printf("Vertical adj of %s between %d and %d\n", t->word, t->start, t->end );
			} 
			if (board->boardTiles[j][i].HorizontalAdjacency != NULL) {
				AdjacencyNode *t = board->boardTiles[j][i].HorizontalAdjacency;
				printf("Horizontal adj of %s between %d and %d\n", t->word, t->start, t->end );
			} 

		}
	}

}

void printTempAdjList(Board *board) {
	AdjacencyNode *head = board->tempAdjacencies;

	while (head != NULL) {
		head = head->next;
	}
}

void LockAdjacencies(Board *board) {
	// printTempAdjList(board);


	if (board->tempAdjacencies == NULL) return;
	AdjacencyNode *h = board->tempAdjacencies;
	while (h!=NULL) {
		AdjacencyNode *temp1 = malloc(sizeof(AdjacencyNode));
		int x1 = h->start % BOARD_SIZE;
		int y1 = h->start / BOARD_SIZE;
		int x2 = h->end % BOARD_SIZE;
		int y2 = h->end / BOARD_SIZE;
		temp1->start = h->start;
		temp1->end = h->end;
		temp1->direction = h->direction;
		strcpy(temp1->word, h->word);
		temp1->next = NULL;
		if (temp1->direction == VERTICAL) {
			board->boardTiles[x1][y1].VerticalAdjacency = temp1;
			board->boardTiles[x2][y2].VerticalAdjacency = temp1;
		} else {
			board->boardTiles[x1][y1].HorizontalAdjacency = temp1;
			board->boardTiles[x2][y2].HorizontalAdjacency = temp1;
		}

		AdjacencyNode *temp2 = malloc(sizeof(AdjacencyNode));
		temp2->start = h->start;
		temp2->end = h->end;
		temp2->direction = h->direction;
		strcpy(temp2->word, h->word);
		temp2->next = board->adjacencyListHead;
		board->adjacencyListHead = temp2;

		h = h->next;
	}

	freeList(board->tempAdjacencies);
	board->tempAdjacencies = NULL;
	return;
}

void RefillTiles(TileBar *tb) {
	for (int i = 0; i < 7; i++) {
		if (tb->playerTiles[i].placed == true) {
			tb->playerTiles[i].val = SelectTile();
			tb->playerTiles[i].placed = false;
		}
	}
	return;
}

bool SubmitWord(UserInterface *ui, int *playerScore) {
	Board *board = &ui->board;
	int location; bool direction;
	char *word[100]; word[0] = '\0';

    int moveScore = 0;

	// flag to indicate whether the word is validly connected to the board
	bool oneConnectionMinimum = false;

	// determine if the letters are placed in a line 
	bool validPlacement = CheckTilePlacement(&board->stagedTiles, &location, &direction);

	if (validPlacement) {

		// if only one tile is placed
		if (ui->board.numStagedTiles == 1) {
			int X = findLow(&board->stagedTiles, HORIZONTAL);
			int Y = findLow(&board->stagedTiles , VERTICAL);

			int check1 = CheckConnection(board, X, Y, VERTICAL, &moveScore);
			int check2 = CheckConnection(board, X, Y, HORIZONTAL, &moveScore);
			if (check1 == CT_VALID || check1 == CT_VALID) {
				if (check1 != CT_INVALID && check2 != CT_INVALID) {
					Lock(board, board->stagedTiles[0], ui->boardTiles);
					board->stagedTiles[0] = NULL;
					LockAdjacencies(board);
					// printAdjacencyLists(board);
                    printf("Your move scored %d points!\n", moveScore);
					RefillTiles(&ui->tilebar);
					return true;
				}
			}
		}


		else if (direction == VERTICAL) {
			int low = findLow(&board->stagedTiles, VERTICAL);
			int high = findHigh(&board->stagedTiles, VERTICAL);
			// check each tile and react accordingly...
			for (int i = low; i <= high; i ++) {
				if (board->boardTiles[location][i].occupied == true) {
					append(word, board->boardTiles[location][i].tile->letter);
					oneConnectionMinimum = true;
				} else {
					int r = CheckConnection(board, location, i, VERTICAL, &moveScore);
					if (r == CT_VALID) {
						append(word, ALPHABET[board->boardTiles[location][i].stval]);
						oneConnectionMinimum = true;
					}
					else if (r == CT_INVALID) {
						break;
					}
					else { 
						append(word, ALPHABET[board->boardTiles[location][i].stval]);
					}
				}

			}

			// mark beginning and end of word
			int beginning = ConvertXYtoIndex(location, low);
			int end = ConvertXYtoIndex(location, high);
			
			// append word to front word and then back word to that
			char *word2[100];
			word2[0] = '\0';
			if (board->boardTiles[location][low - 1].occupied == true) {
				strcpy(word2, board->boardTiles[location][low-1].VerticalAdjacency->word);
				beginning = board->boardTiles[location][low-1].VerticalAdjacency->start;
				oneConnectionMinimum = true;
			}
			strcat(word2, word);
			if (board->boardTiles[location][high + 1].occupied == true) {
				end = board->boardTiles[location][high+1].VerticalAdjacency->end;
				strcat(word2, board->boardTiles[location][high+1].VerticalAdjacency->word);
				oneConnectionMinimum = true;
			}
			
			
			// kinda works, didnt work for adding ED to the bottom of HEAD



			if (oneConnectionMinimum) {
				printf("%s\n", word2);
				fflush(stdout);
				if (validate(word2) ) {
                    moveScore += CalculateScore(word2);
					for (int i = 0; i < 7; i ++){
						if (board->stagedTiles[i] == NULL) break; 
						Lock(board, board->stagedTiles[i], ui->boardTiles);
						board->stagedTiles[i] = NULL;
					}
					// printf("Creating adjacency %s between %d and %d", word, low, high);
					CreateTempAdjacency(beginning, end, VERTICAL, word2, board);
					// printTempAdjList(board);
					LockAdjacencies(board);
					// printAdjacencyLists(board);
                    printf("Your move scored %d points!\n", moveScore);
					// RefillTiles(&ui->tilebar);
					*playerScore = *playerScore + moveScore;
					return true;
				}
			}

		} else if (direction == HORIZONTAL) {
			int low = findLow(&board->stagedTiles, HORIZONTAL);
			int high = findHigh(&board->stagedTiles, HORIZONTAL);

			// check each tile and react accordingly
			for (int i = low; i <= high; i++) {
				// printf("LINE: %d ITERATION (x): %d LOCATION (y): %d\n", __LINE__, i, location);
				if (board->boardTiles[i][location].occupied == true) {
					append(word, board->boardTiles[i][location].tile->letter);
					oneConnectionMinimum = true;
				} else {
					int r = CheckConnection(board, i, location, HORIZONTAL, &moveScore);
					if (r == CT_VALID) {
						append(word, ALPHABET[board->boardTiles[i][location].stval]);
						oneConnectionMinimum = true;
					} else if (r == CT_INVALID) {
						break;
					} else {
						append(word, ALPHABET[board->boardTiles[i][location].stval]);
					}
				}
			}


			// mark beginning and end of word
			int beginning = ConvertXYtoIndex(low, location);
			int end = ConvertXYtoIndex(high, location);
			
			// append word to front word and then back word to that
			char *word2[100];
			word2[0] = '\0';
			if (board->boardTiles[low - 1][location].occupied == true) {
				strcpy(word2, board->boardTiles[low-1][location].HorizontalAdjacency->word);
				beginning = board->boardTiles[low-1][location].HorizontalAdjacency->start;
				oneConnectionMinimum = true;
			}
			strcat(word2, word);
			if (board->boardTiles[high+1][location].occupied == true) {
				end = board->boardTiles[high+1][location].HorizontalAdjacency->end;
				strcat(word2, board->boardTiles[high+1][location].HorizontalAdjacency->word);
				oneConnectionMinimum = true;
			}
			


			if (oneConnectionMinimum) {
				fflush(stdout);
				if (validate(word2)) {
                    moveScore += CalculateScore(word2);
					for (int i = 0; i < 7; i ++){
						if (board->stagedTiles[i] == NULL) break; 
						Lock(board, board->stagedTiles[i], ui->boardTiles);
						board->stagedTiles[i] = NULL;
					}
					CreateTempAdjacency(beginning, end, HORIZONTAL, word2, board);
					printTempAdjList(board);
					LockAdjacencies(board);		
					// printAdjacencyLists(board);
					// RefillTiles(&ui->tilebar);
					*playerScore = *playerScore + moveScore;
					return true;
				}
			}


		}

	}

	// if not valid placement, reject the move
	return false;

}