#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


// Hashing works
// just clean this up and stick it into the scrabble folder
// ideally with the word list... make it neat




#define SIZE 500000

typedef struct Node {
	char word[100];
	struct Node *next; 
} Node;

Node *array[500000];

bool validate(int r, char *s) {

	printf("validating %s...\n", s);

	if (array[r] == NULL) {
		// printf("invalid.\n");
		return false;
	}


	if (strcmp(array[r]->word, s)==0) {
		// printf("valid!\n");
		printf("%s in slot %d, compared to %s\n", array[r]->word, r, s);
		printf("%s matches %s\n", array[r]->word, s);
		return true;
	}
	else {
		// printf("****");
		Node *h = array[r];
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

	// if (array[r] == NULL) printf("*");


	if (array[r] == NULL) {
		// printf("1");
		array[r] = temp;
		// printf("%s\n", array[8]->word);
		return;
	} else {
		// printf("2");
		// printf("Attempting to insert %s into %d. ", s, r);
		// printf("This slot is occupied by %s.\n", array[r]->word);
		Node *h = array[r];
		while (h->next != NULL) {
			h = h->next;
		}
		h->next = temp;
	}

	// printf("%s\n", array[8]->word);

	return;
}

unsigned long hash(unsigned char *str) {
    unsigned long hash = 5381;
    printf("%s\n", str);
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


void Add() {
	char x[100];
	printf("Insert a word to store: ");
	scanf("%s", x);
	unsigned long result = hash(x);
	int r = result % 500000;
	printf("Placing %s in slot %d\n", x, r);
	insert(r, x);
	return;
}

void hash_and_insert(char *word) {
	// printf("...");
	unsigned long result = hash(word);
	int r = result % SIZE;
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

int main(void) {

	char query[10];
	// Add();


	// while (strcmp(decision, "q") != 0){
	// 	printOptions();
	// 	scanf("%s", decision);
	// 	if (strcmp(decision, "i") == 0) Add();
	// 	else if (strcmp(decision, "c") == 0) check();
	// 	else if (strcmp(decision, "p") == 0) printf("Currently stored in 8 is %s\n", array[8]->word);
	// }

	FILE *words;
	// char s[100];
	words = fopen("words_alpha.txt", "r");
	while (!feof(words)) {
		char s[100];
		// printf("%s ", s);
		fscanf(words, "%s", s);
		hash_and_insert(s);
	}
	fclose(words);
	int i = 0;
	while (true) {
		char s[100];
		printf("Search for a word: ");
		scanf("%s", query);
		check(query);
		// printf("Check what is in a slot: ");
		// scanf("%d", &i);
		// printf("%s is in slot %d", array[i]->word, i);
	}




	// while (strcmp(decision, "q") != 0){
	// 	printOptions();
	// 	scanf("%s", decision);
	// 	if (strcmp(decision, "i") == 0) Add();
	// 	else if (strcmp(decision, "c") == 0) check();
	// 	else if (strcmp(decision, "p") == 0) printf("Currently stored in 8 is %s\n", array[8]->word);
	// }








	return 0;
}