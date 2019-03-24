#include <string.h>

typedef struct AdjacencyNode {
    int start;
    int end;
    bool direction;
    char *word[100];
    struct AdjacencyNode *next;
} AdjacencyNode;


AdjacencyNode* AdjacencyNodeConstructor (int s, int e, bool b, char *w, AdjacencyNode *currentHead);