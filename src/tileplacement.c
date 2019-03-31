#include "../include/tileplacement.h"
#include "../include/helper.h"
#include "../include/scoring.h"

void SelectBoardTile(Game *game, Position mousepos) {
	Position p;
	p.x = mousepos.x / 54;
	p.y = mousepos.y / 54;
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



	printf("\n---- DONE CREATING ADJ NODE ---\n");
	// printf("%s starts at %d and ends at %d and is %d", temp->word, temp->start, temp->end, temp->direction);
	return;
}

int CheckConnection(Board *board, int x, int y, bool orientation, int *moveScore) {
	char *word[100];
	word[0] = '\0';

	printf("CHECK CONNECTION LINE: %d\n", __LINE__);
	printf("CURRENT LETTER: %c in %d, %d\n", ALPHABET[board->boardTiles[x][y].stval], x, y);

	printf("Board state...\n");
	PrintBoard(board);

	int tileLoc = ConvertXYtoIndex(x, y); // i am stupid

	// checking for HORIZONTAL adjacencies along each tile
	if (orientation == VERTICAL) {

		bool leftTile;
		bool rightTile;

		printf("CHECK CONNECTION LINE: %d\n", __LINE__);

		// check whether there exists a left or a right tile for the current tile
		if (x != 0) leftTile = board->boardTiles[x-1][y].occupied;
		else leftTile = false;
		if (x != MAXIMUM_INDEX) rightTile = board->boardTiles[x+1][y].occupied;
		else rightTile = false;

		printf("leftTile: %d, rightTile: %d\n", leftTile, rightTile);


		// PrintBoard(board);

		// if tile is on center tile
		if (x == board->center && y == board->center) {
			printf("\nCENTER: %d\n", board->center);
			printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
			append(word, ALPHABET[board->boardTiles[x][y].stval]);
			CreateTempAdjacency(tileLoc, tileLoc, HORIZONTAL, word, board);
					printf("Returning valid.\n");
			return CT_VALID;
		}

		printf("CHECK CONNECTION LINE: %d\n", __LINE__);


		// if left and right tile
		if (leftTile && rightTile) {

			printf("looking at ... %d %d\n", x-1, y);

			printf("Word to left = %s\n", board->boardTiles[x-1][y].HorizontalAdjacency->word);


			printf("CHECK CONNECTION LINE: %d word: %s\n", __LINE__, word);
			strcpy(word,board->boardTiles[x-1][y].HorizontalAdjacency->word);
			printf("cc LINE: %d\n", __LINE__);
			append(word, ALPHABET[board->boardTiles[x][y].stval]);
			printf("cc LINE: %d\n", __LINE__);
			strcpy(word, board->boardTiles[x+1][y].HorizontalAdjacency->word);
			printf("cc LINE: %d\n", __LINE__);
			if (validate(word)) {
				printf("cc LINE: %d\n", __LINE__);

				CreateTempAdjacency(board->boardTiles[x-1][y].HorizontalAdjacency->start, board->boardTiles[x+1][y].HorizontalAdjacency->end, HORIZONTAL, word, board);
                *moveScore += CalculateScore(word);
						printf("Returning valid.\n");
				return CT_VALID;
			} else {
				printf("%s is not a word. returning invalid\n", word);
				return CT_INVALID;
			}
		} 

		// if left tile only
		else if (leftTile) {
			
			
			printf("CHECK CONNECTION LINE: %d\n", __LINE__);
			printf("looking at ... %d %d\n", x-1, y);

			printf("Word to left = %s\n", board->boardTiles[x-1][y].HorizontalAdjacency->word);

			strcpy(word, board->boardTiles[x-1][y].HorizontalAdjacency->word);
			append(word, ALPHABET[board->boardTiles[x][y].stval]);
			if (validate(word)) {
				CreateTempAdjacency(board->boardTiles[x-1][y].HorizontalAdjacency->start, tileLoc, HORIZONTAL, word, board);
                *moveScore += CalculateScore(word);
						printf("Returning valid.\n");
				return CT_VALID;
			} else {
				printf("%s is not a word. returning invalid\n", word);

				return CT_INVALID;
			}
		}


		// if right tile only
		else if (rightTile) {
		printf("CHECK CONNECTION LINE: %d\n", __LINE__);
			
			printf("Line: %d\n", __LINE__);
			append(word, ALPHABET[board->boardTiles[x][y].stval]);
			printf("Word: %s Appending the right tile onto word: %s\n", word, board->boardTiles[x+1][y].HorizontalAdjacency->word);
			strcat(word, board->boardTiles[x+1][y].HorizontalAdjacency->word);
			printf("Word after appending: %s\n", word);
			if (validate(word)) {
				CreateTempAdjacency(tileLoc, board->boardTiles[x+1][y].HorizontalAdjacency->end, HORIZONTAL, word, board);
                *moveScore += CalculateScore(word);
						printf("Returning valid.\n");
				return CT_VALID;
			} else {
				printf("%s is not a word. returning invalid\n", word);

				return CT_INVALID;
			}
		}

		printf("CHECK CONNECTION LINE: %d\n", __LINE__);

		// not connected on the left or right
		append(word, ALPHABET[board->boardTiles[x][y].stval]);
		printf("CHECK CONNECTION LINE: %d\n", __LINE__);
		printf("Not connected on left or right, creating temp adjacency of %s on tile %d\n", word, tileLoc);
		CreateTempAdjacency(tileLoc, tileLoc, HORIZONTAL, word, board);
		printf("Returning none\n");
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

		printf("topTile: %d, bottomTile: %d\n", topTile, bottomTile);


		// check if on center tile
		if (x == board->center && y == board->center) {
			printf("\nCENTER: %d\n", board->center);
			printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
			append(word, ALPHABET[board->boardTiles[x][y].stval]);
			CreateTempAdjacency(tileLoc, tileLoc, VERTICAL, word, board);
					printf("Returning valid.\n");
			return CT_VALID;
		}

		// check for top and bottom tile
		if (topTile && bottomTile) {
			printf("cc LINE: %d\n", __LINE__);


			printf("looking at ... %d %d\n", x, y-1);
			printf("Word above = %s\n", board->boardTiles[x][y-1].VerticalAdjacency->word);

			strcpy(word,board->boardTiles[x][y-1].VerticalAdjacency->word);
			printf("cc LINE: %d\n", __LINE__);
			append(word, ALPHABET[board->boardTiles[x][y].stval]);
			printf("cc LINE: %d\n", __LINE__);
			strcat(word, board->boardTiles[x][y+1].VerticalAdjacency->word);
			printf("cc LINE: %d\n", __LINE__);	
			if (validate(word)) {
			printf("cc LINE: %d\n", __LINE__);
				CreateTempAdjacency(board->boardTiles[x][y-1].VerticalAdjacency->start, board->boardTiles[x][y+1].VerticalAdjacency->end, VERTICAL, word, board);
				printf("cc LINE: %d\n", __LINE__);
	
				*moveScore += CalculateScore(word);
						printf("Returning valid.\n");
				return CT_VALID;
			} else {
				printf("%s is not a word. returning invalid\n", word);

				return CT_INVALID;
			}
		} 

		// check for top tile only
		else if (topTile) {

			
			printf("Got here..?\n");
			printf("looking at ... %d %d\n", x, y-1);

			printf("Word above = %s\n", board->boardTiles[x][y-1].VerticalAdjacency->word);
			printf("Now here?\n");

			strcpy(word, board->boardTiles[x][y-1].VerticalAdjacency->word);
			printf("cc LINE: %d\n", __LINE__);
			append(word, ALPHABET[board->boardTiles[x][y].stval]);
			printf("cc LINE: %d\n", __LINE__);
			if (validate(word)) {
				printf("cc LINE: %d\n", __LINE__);
				CreateTempAdjacency(board->boardTiles[x][y-1].VerticalAdjacency->start, tileLoc, VERTICAL, word, board);
				printf("cc LINE: %d\n", __LINE__);
                *moveScore += CalculateScore(word);
						printf("Returning valid.\n");
				return CT_VALID;
			} else {
				printf("%s is not a word. returning invalid\n", word);

				return CT_INVALID;
			}
		}

		// check for bottom tile only
		else if (bottomTile) {
			printf("looking at ... %d %d\n", x, y-1);

			printf("cc LINE: %d\n", __LINE__);
			append(word, ALPHABET[board->boardTiles[x][y].stval]);
			printf("cc LINE: %d\n", __LINE__);
			strcat(word, board->boardTiles[x][y+1].VerticalAdjacency->word);
			printf("cc LINE: %d\n", __LINE__);
			if (validate(word)) {
				printf("cc LINE: %d\n", __LINE__);
				CreateTempAdjacency(tileLoc, board->boardTiles[x][y+1].VerticalAdjacency->end, VERTICAL, word, board);
				printf("cc LINE: %d\n", __LINE__);

                *moveScore += CalculateScore(word);
						printf("Returning valid.\n");
				return CT_VALID;
			} else {
				printf("%s is not a word. returning invalid\n", word);

				return CT_INVALID;
			}
		}

		// not connected on the TOP or bottom
		append(word, ALPHABET[board->boardTiles[x][y].stval]);
		printf("Not connected on top or bottom, creating temp adjacency of %s on tile %d\n", word, tileLoc);
		CreateTempAdjacency(tileLoc, tileLoc, VERTICAL, word, board);
		printf("returning none\n");
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
	printf("LINE: %d\n", __LINE__);
	int x = st->x_pos;
	int y = st->y_pos;
	printf("LINE: %d\n", __LINE__);

	printf("Locking %c into %d %d\n", ALPHABET[st->tile], x, y);


	printf("-LINE: %d\n", __LINE__);
	board->boardTiles[x][y].occupied = true;
	printf("LINE: %d\n", __LINE__);
	board->boardTiles[x][y].selected = false;
	printf("LINE: %d\n", __LINE__);
	board->boardTiles[x][y].tile = &boardTiles[st->tile];
	printf("LINE: %d\n", __LINE__);
	board->numAIstagedTiles--;
	printf("LINE: %d\n", __LINE__);

	printf("Results: \n");
	printf("Tile occupancy is: %d", board->boardTiles[x][y].occupied);

	// PrintBoard(board);

	return;
}

void RejectMove(UserInterface* ui) {

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
		if (ui->tilebar.playerTiles[i].placed == true) {
			ui->tilebar.playerTiles[i].placed = false;
		}
	}

	freeList(board->tempAdjacencies);
	board->tempAdjacencies = NULL;

	printf("\n\nADJACENCIES POST REJECTION\n\n");
	printAdjacencyLists(&ui->board);

	return;
}

void RejectAIMove(UserInterface *ui) {

	printf("\nRejecting AI move...\n");


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

	printf("\n\nADJACENCIES POST AI REJECTION\n\n");
	printAdjacencyLists(&ui->board);
	printf("Number of staged tiles post rejection: %d\n", board->numAIstagedTiles);
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

	if (head == NULL) printf("\nNo temp adjacencies\n");

	while (head != NULL) {
		if(head->direction == VERTICAL) printf("TEMP Vertical --- ");
		else printf("TEMP Horizontal - ");
		printf("%s between %d and %d\n", head->word, head->start, head->end);
		head = head->next;
	}
}

void LockAdjacencies(Board *board) {
	printf("\n--Locking adjacencies--\n");
	printTempAdjList(board);


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

	printf("Refilling tiles!\n");

	for (int i = 0; i < 7; i++) {
		// printf("%d\n", i);
		if (tb->playerTiles[i].placed == true) {
			tb->playerTiles[i].val = SelectTile();
			tb->playerTiles[i].placed = false;
		}
	}
	return;
}

bool SubmitWord(UserInterface *ui) {
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
					printAdjacencyLists(board);
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
				printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
				if (board->boardTiles[location][i].occupied == true) {
					append(word, board->boardTiles[location][i].tile->letter);
					printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
					oneConnectionMinimum = true;
				} else {
					int r = CheckConnection(board, location, i, VERTICAL, &moveScore);
					if (r == CT_VALID) {
						printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
						append(word, ALPHABET[board->boardTiles[location][i].stval]);
						printf("One connect minimum = true\n");
						oneConnectionMinimum = true;
					}
					else if (r == CT_INVALID) {
						printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
						printf("INVALID\n");
						break;
					}
					else { 
						printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
						printf("%d\n", board->boardTiles[location][i].stval);
						printf("%c\n", ALPHABET[board->boardTiles[location][i].stval]);
						append(word, ALPHABET[board->boardTiles[location][i].stval]);
						// printf("%s\n", word);
					}
				}

			}

			printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
			// mark beginning and end of word
			int beginning = ConvertXYtoIndex(location, low);
			int end = ConvertXYtoIndex(location, high);
			
			// append word to front word and then back word to that
			char *word2[100];
			word2[0] = '\0';
			if (board->boardTiles[location][low - 1].occupied == true) {
				printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
				strcpy(word2, board->boardTiles[location][low-1].VerticalAdjacency->word);
				beginning = board->boardTiles[location][low-1].VerticalAdjacency->start;
				oneConnectionMinimum = true;
			}
			strcat(word2, word);
			if (board->boardTiles[location][high + 1].occupied == true) {
				printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
				end = board->boardTiles[location][high+1].VerticalAdjacency->end;
				strcat(word2, board->boardTiles[location][high+1].VerticalAdjacency->word);
				oneConnectionMinimum = true;
			}
			
			printf("FILE: %s, FUNCTION: %s, LINE: %d\n", __FILE__, __func__, __LINE__);
			
			// kinda works, didnt work for adding ED to the bottom of HEAD



			if (oneConnectionMinimum) {
				printf("%s\n", word2);
				fflush(stdout);
				if (validate(word2) ) {
                    moveScore += CalculateScore(word2);
					printf("VALID WORD! placed vertically\n");
					for (int i = 0; i < 7; i ++){
						if (board->stagedTiles[i] == NULL) break; 
						Lock(board, board->stagedTiles[i], ui->boardTiles);
						board->stagedTiles[i] = NULL;
					}
					if (board->stagedTiles[0] != NULL) printf("Didn't clear staged tiles\n");
					// printf("Creating adjacency %s between %d and %d", word, low, high);
					CreateTempAdjacency(beginning, end, VERTICAL, word2, board);
										printf("Line: %d File: %s\n", __LINE__, __FILE__);
					printTempAdjList(board);
					LockAdjacencies(board);
										printf("Line: %d File: %s\n", __LINE__, __FILE__);
					printAdjacencyLists(board);
										printf("Line: %d File: %s\n", __LINE__, __FILE__);
                    printf("Your move scored %d points!\n", moveScore);
					RefillTiles(&ui->tilebar);
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
						printf("INVALID\n");
						break;
					} else {
						printf("%d\n", board->boardTiles[i][location].stval);
						printf("%c\n", ALPHABET[board->boardTiles[i][location].stval]);
						append(word, ALPHABET[board->boardTiles[i][location].stval]);
						printf("%s\n", word);
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
			
			if (!oneConnectionMinimum) printf("\nWord does not appear to be connected.\n");


			if (oneConnectionMinimum) {
				printf("%s\n", word2);
				fflush(stdout);
				if (validate(word2)) {
                    moveScore += CalculateScore(word2);
					printf("VALID WORD! Placed horizontally\n");
					for (int i = 0; i < 7; i ++){
						if (board->stagedTiles[i] == NULL) break; 
						Lock(board, board->stagedTiles[i], ui->boardTiles);
						board->stagedTiles[i] = NULL;
					}
					if (board->stagedTiles[0] != NULL) printf("Didn't clear staged tiles\n");
					printf("Line: %d File: %s\n", __LINE__, __FILE__);
					CreateTempAdjacency(beginning, end, HORIZONTAL, word2, board);
					printf("Line: %d File: %s\n", __LINE__, __FILE__);
					printTempAdjList(board);
					LockAdjacencies(board);		
					printf("Line: %d File: %s\n", __LINE__, __FILE__);
					printAdjacencyLists(board);
                    printf("Your move scored %d points!\n", moveScore);
					RefillTiles(&ui->tilebar);
					return true;
				}
			}


		}

	}

	// if not valid placement, reject the move
	RejectMove(ui);
	return false;

}