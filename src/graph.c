#include "../include/graph.h"
#include <stdbool.h>
#include "../include/types.h"

AdjacencyNode* AdjacencyNodeConstructor (int s, int e, bool b, char *w, AdjacencyNode *currentHead) {
    AdjacencyNode *temp;
    temp->start = s;
    temp->end = e;
    temp->direction = b;
    strcpy(temp->word, w);
    temp->next = currentHead;
    return temp;
}


