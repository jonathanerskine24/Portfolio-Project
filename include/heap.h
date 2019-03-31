#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct Move {
	int moveValue;
	int location;
	char root[100];
	char word[100];
	bool orientation;
} Move;

struct heap {
	int size;
	int count;
	struct Move *heaparr;
};

static int *heap;

// size is the current maximum capacity of the heap
static int size;

// count is the number of items in the heap
static int count;

static int initial_size = 4;

struct Move InitMove(int value, int location, char *root, char *word, bool orientation);

void heap_init(struct heap *h);

void max_heapify(struct Move *data, int loc, int count);

void heap_push(struct heap *h, struct Move newMove);

void heap_display(struct heap *h);

struct Move heap_delete(struct heap *h);

int emptyPQ(struct heap *pq);