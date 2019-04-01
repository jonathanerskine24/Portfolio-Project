#include "types.h"
#include "trie.h"

typedef struct StackNode {
    int index;
    int length;
    bool orientation;
    int letter;
    struct StackNode* next;
} StackNode;

// I feel like this is the wrong way to do this, but this is technically O(1) and doesnt take forever to run so
// I'm going to roll with this unless I find something better
void TryAllPermutations(struct heap *h, char *s, char *root, int room, int location, bool orientation);

StackNode* FindAllValidTiles(Board *b);

void PlaceWord(UserInterface *ui, int*, int*);

void AI_Move(Game *game);