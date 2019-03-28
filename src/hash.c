#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/hash.h"


bool validate(char *s) {

	unsigned long result = hash(s);
	int index = result % 500000;
	
	if (validWords[index] == NULL) {
		return false;
	}

	if (strcmp(validWords[index]->word, s)==0) {
		return true;
	} else {
		Node *h = validWords[index];
		while (h->next != NULL) {
			h = h->next;
			if (strcmp(h->word, s)==0) {
				return true;
			}
		}
	}
	return false;
}

void insert(int r, char *s) {
	Node *temp = malloc(sizeof(Node));
	strcpy(temp->word, s);
	temp->next = NULL;

	if (validWords[r] == NULL) {
		validWords[r] = temp;
		return;
	} else {
		Node *h = validWords[r];
		while (h->next != NULL) {
			h = h->next;
		}
		h->next = temp;
	}

	return;
}

unsigned long hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while (c = *str++) {
        hash = ((hash << 5) + hash) + c;
    }

    return hash;
}

void printOptions(void) {
	printf("Insert or check?\n");
	printf("i: insert \nc: check\nq: quit\n");
	return;
}

void hash_and_insert(char *word) {
	unsigned long result = hash(word);
	int r = result % 500000;
	insert(r, word);
	return;
}

void LoadDictionary(void) {
	FILE *words;

	words = fopen("resources/words_alpha.txt", "r");

	if (words == NULL) {
		printf("Failed to open file.\n"); 
		perror("Error: ");
	} 

	while (!feof(words)) {
		char s[100];
		fscanf(words, "%s", s);
		hash_and_insert(s);
	}

	fclose(words);
}











