#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/hash.h"


// Hashing works
// just clean this up and stick it into the scrabble folder
// ideally with the word list... make it neat


bool validate(int r, char *s) {

	printf("validating %s...\n", s);

	if (validWords[r] == NULL) {
		// printf("invalid.\n");
		return false;
	}


	if (strcmp(validWords[r]->word, s)==0) {
		// printf("valid!\n");
		printf("%s in slot %d, compared to %s\n", validWords[r]->word, r, s);
		printf("%s matches %s\n", validWords[r]->word, s);
		return true;
	}
	else {
		// printf("****");
		Node *h = validWords[r];
		while (h->next != NULL) {
			h = h->next;
			if (strcmp(h->word, s)==0) {
				printf("%s in slot %d, compared to %s\n", h->word, r, s);

				// printf("~~~%s~~~\n", h->word);
				// printf("valid!\n");
				return true;
			}
		}
		// printf("invalid.\n");
	}
	// return false;
}

void insert(int r, char *s) {
	// printf("***");

	Node *temp = malloc(sizeof(Node));
	strcpy(temp->word, s);
	temp->next = NULL;

	// if (validWords[r] == NULL) printf("*");


	if (validWords[r] == NULL) {
		// printf("1");
		validWords[r] = temp;
		// printf("%s\n", validWords[8]->word);
		return;
	} else {
		Node *h = validWords[r];
		while (h->next != NULL) {
			h = h->next;
		}
		h->next = temp;
	}

	// printf("%s\n", validWords[8]->word);

	return;
}

unsigned long hash(unsigned char *str) {
    unsigned long hash = 5381;
    // printf("%s\n", str);
    int c;

    while (c = *str++) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }

    return hash;
}

void printOptions(void) {
	printf("Insert or check?\n");
	printf("i: insert \nc: check\nq: quit\n");
	return;
}



void hash_and_insert(char *word) {
	// printf("...");
	unsigned long result = hash(word);
	int r = result % 500000;
	insert(r, word);
	return;
}

void check(char *word) {
	// char x[100];
	// printf("\nInsert a word to check: ");
	// scanf("%s", x);
	unsigned long result = hash(word);
	int r = result % 500000;
	if (validate(r, word)) printf("valid\n");
	else printf("invalid\n");
	return;
}

void LoadDictionary(void) {
	FILE *words;
	// char s[100];
	words = fopen("resources/words_alpha.txt", "r");
	if (words == NULL) {
		printf("Failed to open file.\n"); 
		perror("Error: ");
	} 
	// else printf("Successfully opened file.\n");
	// printf("Opened!");
	fflush(stdout);
	while (!feof(words)) {
		// printf("!");
		// fflush(stdout);
		char s[100];
		// printf("%s ", s);
		fscanf(words, "%s", s);
		hash_and_insert(s);
	}
	fclose(words);
}

// int main(void) {

// 	char query[10];



// 	FILE *words;
// 	// char s[100];
// 	words = fopen("words_alpha.txt", "r");
// 	while (!feof(words)) {
// 		char s[100];
// 		// printf("%s ", s);
// 		fscanf(words, "%s", s);
// 		hash_and_insert(s);
// 	}
// 	fclose(words);
// 	int i = 0;
// 	while (true) {
// 		char s[100];
// 		printf("Search for a word: ");
// 		scanf("%s", query);
// 		check(query);
// 		// printf("Check what is in a slot: ");
// 		// scanf("%d", &i);
// 		// printf("%s is in slot %d", validWords[i]->word, i);
// 	}


// 	return 0;
// }