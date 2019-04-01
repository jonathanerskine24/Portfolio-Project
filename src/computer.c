#include "../include/computer.h"
#include "../include/scoring.h"
#include "../include/helper.h"
#include "../include/heap.h"
#include "../include/tileplacement.h"

bool CreateStagedTile (Board *b, int tileLocation, int tile) {

	int x = tileLocation % BOARD_SIZE;
	int y = tileLocation / BOARD_SIZE;

    if (b->boardTiles[x][y].occupied == true) {
		return false;
	} 
	StagedTile *temp = malloc(sizeof(StagedTile));

	temp->tile  = tile;
	temp->x_pos = x;
	temp->y_pos = y;

	b->AIstagedTiles[b->numAIstagedTiles] = temp;
    b->numAIstagedTiles++;
	b->boardTiles[x][y].stval = tile;


	return true;

}


bool StageTilesForMove(Move *move, Board *b) {
    char root[100]; char word[100];
    root[0] = '\0'; word[0] = '\0';

    strcpy(root, move->root);
    strcpy(word, move->word);

    int rootLen = strlen(root);
    int wordLen = strlen(word);
    int locationModifier = 1;
    
    // used for keeping track of location
    int n = 1;

    if (move->orientation == VERTICAL) locationModifier = BOARD_SIZE;

    bool flag = true;

    for (int i = rootLen; i < wordLen; i ++) {
        flag = CreateStagedTile(b, (move->location + (n * locationModifier)), word[i] - 97);
        if (flag = false) return false;
        n++;
    }

    return true;
    
}


void AddMoveToHeap(struct heap* theHeap, char *word, char *root, int location, bool orientation) {

    Move newMove = InitMove(CalculateScore(word), location, root, word, orientation);
    heap_push(theHeap, newMove);

    return;
}

// I feel like this is the wrong way to do this, but this is technically O(1) and doesnt take forever to run so
// I'm going to roll with this unless I find something better
void TryAllPermutations(struct heap *theHeap, char *s, char *root, int room, int location, bool orientation) {


    // printf("LINE : %d\n", __LINE__);
    char temp[100]; temp[0] = '\0';
    strcpy(temp, root);

    for (int i = 0; i < 7; i ++) { // adding first letter
        char temp2[100]; strcpy(temp2, temp);
        append(temp, (char)s[i]);
        if (validate(temp)) AddMoveToHeap(theHeap, temp, root, location, orientation);


        // printf("LINE : %d %s\n", __LINE__, temp);
        for (int j = 0; j < 7; j++) { // adding second letter

            if (room == 1) break;
            char copy[100]; strcpy(copy, temp);


            if (j != i) {
                // printf("LINE : %d %s\n", __LINE__, temp);
                append(temp, s[j]);
                // printf("LINE : %d %s\n", __LINE__, temp);
                if (validate(temp)) AddMoveToHeap(theHeap, temp, root, location, orientation);


                // printf("LINE : %d %s\n", __LINE__, temp);
                for (int k = 0; k < 7; k++) { // adding third letter


                    // printf("LINE : %d %s\n", __LINE__, temp);
                    if (room == 2) break;
                    char copy2[100]; strcpy(copy2, temp);
                    if (k != i && k != j) {
                        append(temp, s[k]);
                        if (validate( temp)) AddMoveToHeap(theHeap, temp, root, location, orientation);

                        for (int l = 0; l < 7; l++) { // adding fourth letter

                            // printf("LINE : %d %s\n", __LINE__, temp);
                            if (room == 3) break;
                            char copy3[100]; strcpy(copy3, temp);
                            if (l != k && l != j && l != i) {
                                append(temp, s[l]);
                                if (validate(temp)) AddMoveToHeap(theHeap, temp, root, location, orientation);

                                for (int m = 0; m < 7; m++){ // adding 5th letter

                                    //  printf("LINE : %d %s\n", __LINE__, temp);
                                    if (room == 4) break;
                                    char copy4[100]; strcpy(copy4, temp);
                                    if (m != l && m != k && m != j && m != i) {
                                        append(temp, s[m]);
                                        if (validate(temp)) AddMoveToHeap(theHeap, temp, root, location, orientation);

                                        for (int n = 0; n < 7; n++){ // adding 6th letter
                                            // printf("LINE : %d %s\n", __LINE__, temp);
                                            if (room == 5) break;
                                            char copy5[100]; strcpy(copy5, temp);
                                            if (n != l && n != k && n != j && n != i && n != m) {
                                                append(temp, s[n]);
                                                if (validate( temp)) AddMoveToHeap(theHeap, temp, root, location, orientation);

                                                for (int o = 0; o < 7; o++){ // adding 7th letter
                                                    // printf("LINE : %d %s\n", __LINE__, temp);
                                                    if (room == 6) break;
                                                    char copy6[100]; strcpy(copy6, temp);
                                                    if (o != l && o != k && o != j && o != i && o != n && o != m ) {
                                                        append(temp, s[o]);
                                                        if (validate(temp)) AddMoveToHeap(theHeap, temp, root, location, orientation);
                                                    }   
                                                }
                                            strcpy(temp, copy5);
                                            }
                                        }
                                    strcpy(temp, copy4);
                                    }
                                }
                            strcpy(temp, copy3);
                            } 
                        }
                    strcpy(temp, copy2);
                    }
                }
            strcpy(temp, copy);
            }
        strcpy(temp, temp2);
        }
    }
    return;
}

bool TryWord(Board *board, char *word) {
}

bool TileIsOpen(Board *b, int x, int y) {
    if (b->boardTiles[x][y].occupied == true) return false;
    else return true;
}

void PlaceWord(UserInterface *ui, int *totalScore, int *consecutivePasses) {

    // initialize heap for storing words
    struct heap movesHeap;
    heap_init(&movesHeap);

    Board *b = &ui->board;


    AdjacencyNode *head = b->adjacencyListHead;

    char computerTiles[8];
    computerTiles[0] = '\0';


    for (int i = 0; i < 7; i ++) {
        append(computerTiles, ALPHABET[ui->player2orAI.playerTiles[i].val]);
    }




    // check for all possible moves given availible tile locations, length of open slot, and our tiles
    while (head != NULL) {


        if (head->direction == VERTICAL) {
            int x = head->end % BOARD_SIZE;
            int y = head->end / BOARD_SIZE;



            if (b->boardTiles[x][y+1].occupied == false) {

                int length = 0;

                while (length <= 7 && b->boardTiles[x][y+length+2].occupied == false && length + y < BOARD_SIZE - 1) {
                    length ++;
                }


                if (length != 0) TryAllPermutations(&movesHeap, computerTiles, b->boardTiles[x][y].VerticalAdjacency->word, length, head->end, VERTICAL);
            }


        } else if (head->direction == HORIZONTAL) {
            int x = head->end % BOARD_SIZE;
            int y = head->end / BOARD_SIZE;



            // printf("%s -> \n", head->word);
            if (b->boardTiles[x+1][y].occupied == false) {
                // printf("occupied: %d, %s\n" , b->boardTiles[x+1][y].occupied, head->word);

                int length = 0;

                while (length <= 7 && b->boardTiles[x+length+2][y].occupied == false && (length + x) < MAXIMUM_INDEX) {
                    length ++;
                }


                // printf("LINE : %d\n", __LINE__);
                // printf("Trying %s, %s, %d\n", computerTiles, head->word, length);
                TryAllPermutations(&movesHeap, computerTiles, b->boardTiles[x][y].HorizontalAdjacency->word, length, head->end, HORIZONTAL);
            }

            // printf("We can place %s for %d points\n", move.word, move.val);

        }

        head = head->next;
    }

    int initCount = movesHeap.count;
    int n = 0;

    if (movesHeap.count == 0) {
        RefillTiles(&ui->player2orAI);
        return;
    }

    while (movesHeap.count > 0) {
        if (n == initCount) {
            SwapTiles(&ui->player2orAI);
            *consecutivePasses = *consecutivePasses + 1;
        }

        if (consecutivePasses == 3) {
            return;
        }


        int connectionType = CT_NONE;

        // remove the current highest theoretical move
        Move current = heap_delete(&movesHeap);
        n++;
        int moveScore = current.moveValue;

        if (moveScore > 100) break;


        // place the move on the board
        // these tiles are "placed" but not rendered
        bool successfulStage = StageTilesForMove(&current, b);

        if (!successfulStage) {
            RejectAIMove(ui);
            break;
        }

        int x = current.location % BOARD_SIZE;
        int y = current.location / BOARD_SIZE;

        int modifier = 1;



        // printf("LINE: %d\n", __LINE__);

        // printTempAdjList(b);

        if (current.orientation == VERTICAL) {
            modifier = BOARD_SIZE;
            for (int i = 1; i <= b->numAIstagedTiles; i++) {
                int result = CheckConnection(b, x, y + i, VERTICAL, &moveScore);
                if (result == CT_INVALID) {
                    connectionType = CT_INVALID;
                    break;
                }
            }
        } else {
            for (int i = 1; i <= b->numAIstagedTiles; i++) {
                int result = CheckConnection(b, x + i, y, HORIZONTAL, &moveScore);
                if (result == CT_INVALID || !TileIsOpen(b, x + i, y)) {
                    connectionType = CT_INVALID;
                    break;   
                }
            }
        }


        if (connectionType != CT_INVALID) {


            int s = current.location - (strlen(current.root) * modifier) + modifier;
            int e = s + (strlen(current.word) * modifier) - modifier;


            for (int i = 0; i < 7; i ++){
                if (b->AIstagedTiles[i] == NULL) {
                    break;
                }

                for (int j = 0; j < 7; j++) {
                    if (b->AIstagedTiles[i]->tile == ui->player2orAI.playerTiles[j].val && ui->player2orAI.playerTiles[j].placed == false) {
                        ui->player2orAI.playerTiles[j].placed = true;
                        break;
                    }
                }

                if (b->AIstagedTiles[i]->tile == ui->player2orAI.playerTiles[i].val) {
                    ui->player2orAI.playerTiles[i].placed = true;
                }

                LockAI(b, b->AIstagedTiles[i], ui->boardTiles);
                b->AIstagedTiles[i] = NULL;
            }


            CreateTempAdjacency(s, e, current.orientation, current.word, b);

            LockAdjacencies(b);
            // printAdjacencyLists(b);
            *totalScore = *totalScore + moveScore;

            printf("Your move scored %d points!\n", moveScore);
            RefillTiles(&ui->player2orAI);
            *consecutivePasses = 0;
            emptyPQ(&movesHeap);


            break;
        }


        RejectAIMove(ui);


    }    

}

void AI_Move(Game *game) {
    PlaceWord(&game->ui, &game->gameinfo.player2score, &game->gameinfo.player2consecutivePasses);
}