#pragma once
#include <stdbool.h>

// table array item
typedef struct Node {
	char word[100];
	struct Node *next; 
} Node;

Node *validWords[500000];

// confirm whether a word is in the table
bool validate(char *s);

// insert a word into the table
void insert(int r, char *s);

// generate a hash
unsigned long hash(unsigned char *str);

// hash a word and insert it into the table
void hash_and_insert(char *word);

void LoadDictionary(void);

// used to print valid or invalid for a word, terminal use only
void check(char *word);

