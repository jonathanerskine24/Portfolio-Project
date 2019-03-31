#include "../include/computer.h"
#include "../include/scoring.h"
#include "../include/helper.h"
#include "../include/heap.h"
#include "../include/tileplacement.h"

void CreateStagedTile (Board *b, int tileLocation, int tile) {
    printf("Tile Location: %d\n", tileLocation);
    printf("Tile val: %d\n", tile);

	int x = tileLocation % BOARD_SIZE;
	int y = tileLocation / BOARD_SIZE;

	StagedTile *temp = malloc(sizeof(StagedTile));

	temp->tile  = tile;
	temp->x_pos = x;
	temp->y_pos = y;

	b->AIstagedTiles[b->numAIstagedTiles] = temp;
    b->numAIstagedTiles++;
	b->boardTiles[x][y].stval = tile;

    printf("Num staged: %d\n", b->numAIstagedTiles);

	return;

}


void StageTilesForMove(Move *move, Board *b) {
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

    for (int i = rootLen; i < wordLen; i ++) {
        CreateStagedTile(b, (move->location + (n * locationModifier)), word[i] - 97);
        n++;
    }


    return;
    
}


void AddMoveToHeap(struct heap* theHeap, char *word, char *root, int location, bool orientation) {
    // printf("Got here\n");
    Move newMove = InitMove(CalculateScore(word), location, root, word, orientation);
    // printf("Test\n");
    heap_push(theHeap, newMove);
    // printf("Also got here\n");
    return;
}

// I feel like this is the wrong way to do this, but this is technically O(1) and doesnt take forever to run so
// I'm going to roll with this unless I find something better
void TryAllPermutations(struct heap *theHeap, char *s, char *root, int room, int location, bool orientation) {


    // printf("LINE : %d\n", __LINE__);
    char temp[100]; temp[0] = '\0';
    strcpy(temp, root);


    // printf("LINE : %d\n", __LINE__);


    // printf("LINE : %d\n", __LINE__);
    for (int i = 0; i < 7; i ++) { // adding first letter
        char temp2[100]; strcpy(temp2, temp);
        append(temp, (char)s[i]);
        if (validate(temp)) AddMoveToHeap(theHeap, temp, root, location, orientation);


        // printf("LINE : %d %s\n", __LINE__, temp);
        for (int j = 0; j < 7; j++) { // adding second letter

            if (room == 1) break;
            char copy[100]; strcpy(copy, temp);

            // printf("LINE : %d %s\n", __LINE__, temp);
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

void PlaceWord(UserInterface *ui) {

    // initialize heap for storing words
    struct heap movesHeap;
    heap_init(&movesHeap);

    Board *b = &ui->board;

    printf("LINE : %d\n", __LINE__);

    AdjacencyNode *head = b->adjacencyListHead;

    char computerTiles[8];
    computerTiles[0] = '\0';

    printf("LINE : %d\n", __LINE__);

    for (int i = 0; i < 7; i ++) {
        append(computerTiles, ALPHABET[ui->player2orAI.playerTiles[i].val]);
    }

    printf("~~~~~%s~~~~~\n", computerTiles);

    printf("LINE : %d\n", __LINE__);

    if (head == NULL) printf("head is null\n");

    // check for all possible moves given availible tile locations, length of open slot, and our tiles
    while (head != NULL) {

        if (head->direction == VERTICAL) {
            int x = head->end % BOARD_SIZE;
            int y = head->end / BOARD_SIZE;



            printf("%s -> \n", head->word);
            if (b->boardTiles[x][y+1].occupied == false) {
                printf("occupied: %d, %s\n" , b->boardTiles[x][y+1].occupied, head->word);

                int length = 0;

                while (length <= 7 && b->boardTiles[x][y+length+2].occupied == false && length + y < BOARD_SIZE - 1) {
                    length ++;
                }


                // printf("LINE : %d\n", __LINE__);
                // printf("Trying %s, %s, %d\n", computerTiles, head->word, length);
                if (length != 0) TryAllPermutations(&movesHeap, computerTiles, b->boardTiles[x][y].VerticalAdjacency->word, length, head->end, VERTICAL);
            }

            // printf("We can place %s for %d points\n", move.word, move.val);

        } else if (head->direction == HORIZONTAL) {
            int x = head->end % BOARD_SIZE;
            int y = head->end / BOARD_SIZE;



            // printf("%s -> \n", head->word);
            if (b->boardTiles[x+1][y].occupied == false) {
                printf("occupied: %d, %s\n" , b->boardTiles[x+1][y].occupied, head->word);

                int length = 0;

                while (length <= 7 && b->boardTiles[x+length+2][y].occupied == false && (length + x) < MAXIMUM_INDEX) {
                    length ++;
                }


                // printf("LINE : %d\n", __LINE__);
                printf("Trying %s, %s, %d\n", computerTiles, head->word, length);
                TryAllPermutations(&movesHeap, computerTiles, b->boardTiles[x][y].HorizontalAdjacency->word, length, head->end, HORIZONTAL);
            }

            // printf("We can place %s for %d points\n", move.word, move.val);

        }

        head = head->next;
    }



    printf("Done with adjacency list!\n");
    printf("Num words added: %d\n", movesHeap.count);
    int initCount = movesHeap.count;
    // Move temp = heap_delete(&movesHeap);
    // printf("Highest scoring word is %s, scoring %d\n", temp.word, temp.moveValue);
    // after we have created a max heap of moves, iterate through the heap top down to find a move that works
    int n = 0;

    if (movesHeap.count == 0) {
        "\n\n\nNo moves were found.\n\n\n";
        return;
    }

    while (movesHeap.count > 0) {
        printf("Line: %d\n", __LINE__);
        if (n == initCount) printf("\n\n\n\n\n\n\n\nHOLY FUCK MAN YOU WENT THROUGH ALL THE MOVES\n\n\n\n\n\n\n\n\n\n\n\n\n");

        int connectionType = CT_NONE;


        // remove the current highest theoretical move
        Move current = heap_delete(&movesHeap);
        n++;
        int moveScore = current.moveValue;

        printf("Starting to evaluate word number %d: %s -- LINE: %d\n", n, current.word, __LINE__);


        printf("LINE: %d\n", __LINE__);
        // place the move on the board
        // these tiles are "placed" but not rendered
        StageTilesForMove(&current, b);
        printf("LINE: %d\n", __LINE__);

        int x = current.location % BOARD_SIZE;
        int y = current.location / BOARD_SIZE;

        int modifier = 1;

        printf("Our current root word ends on tile %d, aka (%d,%d)\n", current.location, x, y);


        // printf("LINE: %d\n", __LINE__);

        printTempAdjList(b);

        if (current.orientation == VERTICAL) {
            printf("LINE: %d\n", __LINE__);
            modifier = BOARD_SIZE;
            printf("Trying : %s with a value of %d\n", current.word, current.moveValue);
            printf("Have %d staged tiles.\n", b->numAIstagedTiles);
            for (int i = 1; i <= b->numAIstagedTiles; i++) {
                printf("\nAI Vertical Test %d / %d Starting\n", i, b->numAIstagedTiles);
                printf("%s -- We are passing %d, %d, to CheckConnection!\n", current.word, x, y + i);
                printf("X: %d Y: %d  Y + i: %d\n", x, y, y + i);
                int result = CheckConnection(b, x, y + i, VERTICAL, &moveScore);
                if (result == CT_INVALID) {
                    printf("Cannot place %s, moving on!\n", current.word);
                    connectionType = CT_INVALID;
                    break;
                }
                printf("\nAI Vertical Test %d / %d Complete\n", i, b->numAIstagedTiles);
            }
            printf("Got here 1\n");
        } else {
             printf("LINE: %d\n", __LINE__);
            for (int i = 1; i <= b->numAIstagedTiles; i++) {
                printf("\nAI Horizontal Test %d / %d Starting\n", i, b->numAIstagedTiles);
                printf("%s -- We are passing %d, %d, to CheckConnection!\n", current.word, x + i,y);
                int result = CheckConnection(b, x + i, y, HORIZONTAL, &moveScore);
                printf("X: %d, X+i: %d, Y: %d \n", x, x + i, y );
                if (result == CT_INVALID) {
                    printf("\n\nCannot place %s, moving on!\n\n", current.word);
                    connectionType = CT_INVALID;
                    break;   
                }
                printf("\nAI Horizontal Test %d / %d complete\n", i, b->numAIstagedTiles);
            }
            printf("Got here 2\n");
        }

        printf("Line: %d\n", __LINE__);
        printf("Got here 3: ConnectType = %d\n", connectionType);
        fflush(stdout);

        if (connectionType != CT_INVALID) {
            printf("We can place %s at location %d\n", current.word, current.location);
            printf("~~~~~~VALID WORD!\n");

            printf("Checking important values:\n");
            printf("Number of AI staged tiles: %d\n", ui->board.numAIstagedTiles);
            printf("Number of AI staged tiles pt 2: %d\n", b->numAIstagedTiles);
            printf("AI tiles: %s\n", computerTiles);

            int s = current.location - (strlen(current.root) * modifier) + modifier;
            int e = s + (strlen(current.word) * modifier) - modifier;

            if (b->numAIstagedTiles == 0)  printf("no staged tiles..\n");
            else printf("Num staged tiles : %d\n", b->numAIstagedTiles);

            // bool occupiedFlag = false;

            // for (int i = 0; i < 7; i++) {
            //     if (b->boardTiles[b->AIstagedTiles[i]->x_pos][b->AIstagedTiles[i]->y_pos].occupied == true) {
            //         occupiedFlag=true;
            //     }
            // }

            // if (occupiedFlag == true) break;

            for (int i = 0; i < 7; i ++){
                printf("LINE: %d, %d\n", __LINE__, i);
                if (b->AIstagedTiles[i] == NULL) {
                    if (i == 0) printf("Somethin fucked up.... line : %d\n", __LINE__);
                    break;
                } 
                if (b->AIstagedTiles[i]->tile == ui->player2orAI.playerTiles[i].val) {
                    ui->player2orAI.playerTiles[i].placed = true;
                }
                printf("LINE: %d\n", __LINE__);         
                LockAI(b, b->AIstagedTiles[i], ui->boardTiles);
                printf("\nIs this occupied? %d\n", b->boardTiles[b->AIstagedTiles[i]->x_pos][b->AIstagedTiles[i]->y_pos].occupied);
                printf("Is THIS occupied? %d\n", ui->board.boardTiles[b->AIstagedTiles[i]->x_pos][b->AIstagedTiles[i]->y_pos].occupied);
                printf("LINE: %d\n", __LINE__);
                b->AIstagedTiles[i] = NULL;
            }

            printf("LINE: %d\n", __LINE__);
            if (b->AIstagedTiles[0] != NULL) printf("Didn't clear staged tiles\n");
            // printf("Creating adjacency %s between %d and %d", word, low, high);

            // int s = current.location - (strlen(current.root) * modifier) + modifier;
            // int e = s + (strlen(current.word) * modifier) - modifier;

            CreateTempAdjacency(s, e, current.orientation, current.word, b);

            printf("LINE: %d\n", __LINE__);
            LockAdjacencies(b);
            printf("LINE: %d\n", __LINE__);

            printf("\n\n\n::::CURRENT ADJACENCIES::::\n");
            printAdjacencyLists(b);
            printf("END CURRENT ADJACENCIES:::\n\n\n");


            printf("LINE: %d\n", __LINE__);
            printf("Your move scored %d points!\n", moveScore);
            printf("LINE: %d\n", __LINE__);
            RefillTiles(&ui->player2orAI);
            printf("LINE: %d\n", __LINE__);
            emptyPQ(&movesHeap);
            printf("LINE: %d\n", __LINE__);

            break;
        }

        printf("LINE: %d\n", __LINE__);
        fflush(stdout);

        RejectAIMove(ui);


    }    



    printf("LINE : %d\n", __LINE__);

}

void AI_Move(Game *game) {
    PlaceWord(&game->ui);
}