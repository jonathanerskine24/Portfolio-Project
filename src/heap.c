#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../include/types.h"


struct Move InitMove(int value, int location, char *root, char *word, bool orientation) {
	struct Move newMove;
	newMove.moveValue = value;
	newMove.location = location;
	strcpy(newMove.word, word);
	strcpy(newMove.root, root);
	newMove.orientation = orientation;
	return newMove;
}

// int *heap, size, count;
// int initial_size = 4;

void heap_init(struct heap *h) {
	h->count = 0;
	h->size = initial_size;
	h->heaparr = (struct Move*) malloc(sizeof(struct Move) * 4);
	if(!h->heaparr) {
		printf("Error allocating memory...\n");
		exit(-1);
	}

}

void max_heapify(struct Move *data, int loc, int count) {
	int left, right, largest;

	struct Move temp;

	left = 2*(loc) + 1;
	right = left + 1;
	largest = loc;
	

	if (left <= count && data[left].moveValue > data[largest].moveValue) {
		largest = left;
	} 
	if (right <= count && data[right].moveValue > data[largest].moveValue) {
		largest = right;
	} 
	
	if(largest != loc) {
		temp = data[loc];
		data[loc] = data[largest];
		data[largest] = temp;
		max_heapify(data, largest, count);
	}

}

void heap_push(struct heap *h, struct Move newMove) {
	int index = 0;
	int parent = 0 ;

	// printf("Adding node to heap!\n");
	// printf("Word: %s\nRoot: %s\nScore: %d\nLocation: %d\n", newMove.root, newMove.word, newMove.moveValue, newMove.location);
 
	// Resize the heap if it is too small to hold all the data
	if (h->count == h->size)
	{
		// printf("resizing\n");
		h->size += 1;
		h->heaparr = realloc(h->heaparr, sizeof(struct Move) * (h->size * 2 ));
		if (!h->heaparr) exit(-1); // Exit if the memory allocation fails
	}
 	
 	index = h->count++; // First insert at last of array

 	// Find out where to put the element and put it
	for(;index; index = parent)
	{
		// printf("%d\n", parent);
		parent = (index - 1) / 2;
		if (h->heaparr[parent].moveValue >= newMove.moveValue) break;
		h->heaparr[index] = h->heaparr[parent];
	}
	h->heaparr[index] = newMove;

	// printf("Finished adding to heap!\n");
}

void heap_display(struct heap *h) {
	int i;
	for(i=0; i<h->count; ++i) {
		printf("|%d, %s|", h->heaparr[i].moveValue, h->heaparr[i].word);
	}
	printf("\n");
}

struct Move heap_delete(struct heap *h) {
	struct Move removed;
	struct Move temp = h->heaparr[--h->count];
 	
	
	if ((h->count <= (h->size / 2)) && (h->size > initial_size))
	{
		// printf("\nCount is now : %d\n", h->count);
		// printf("Resizing heap from %d to ", h->size);
		h->size = h->size / 2;
		// printf("%d\n", h->size);
		h->heaparr = realloc(h->heaparr, sizeof(struct Move) * h->size);
		if (!h->heaparr) exit(-1); // Exit if the memory allocation fails
	}
 	removed = h->heaparr[0];
 	h->heaparr[0] = temp;
 	max_heapify(h->heaparr, 0, h->count);
 	return removed;
}



int emptyPQ(struct heap *pq) {
	int i;
	while(pq->count != 0) {
		Move move = heap_delete(pq);
		// if (move.moveValue > 20) {
			// printf("\nWord: %s Root: %s Location: %d Value: %d\n", move.word, move.root, move.location, move.moveValue);
		// }
		
		// printf("<<%d ", move.moveValue);
	}
}
