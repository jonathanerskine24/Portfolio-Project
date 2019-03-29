#include "../include/types.h"

#define ALPHABET_SIZE 26
#define CHAR_TO_INDEX(c) ((int)c - (int)'a') 

TrieNode *getNode(void) { 

	TrieNode *pNode = NULL; 

	pNode = (TrieNode *)malloc(sizeof(struct TrieNode)); 

	if (pNode) { 
		int i; 

		pNode->isEndOfWord = false; 

		for (i = 0; i < ALPHABET_SIZE; i++) 
			pNode->children[i] = NULL; 
	} 

	return pNode; 
} 

void insert(const char *key) { 
    int level; 
    int length = strlen(key); 
    int index; 
  
    struct TrieNode *pCrawl = root; 
  
    for (level = 0; level < length; level++) 
    { 
        index = CHAR_TO_INDEX(key[level]); 
        if (!pCrawl->children[index]) 
            pCrawl->children[index] = getNode(); 
  
        pCrawl = pCrawl->children[index]; 
    } 
  
    pCrawl->isEndOfWord = true; 
} 

bool validate(const char *key) {     
    int length = strlen(key); 
    int index; 

    struct TrieNode *pCrawl = root; 
  
    for (int level = 0; level < length; level++) 
    { 
        index = CHAR_TO_INDEX(key[level]); 
  
        if (!pCrawl->children[index]) 
            return false; 
  
        pCrawl = pCrawl->children[index]; 
    } 
  
    return (pCrawl != NULL && pCrawl->isEndOfWord); 
} 
  


void LoadDictionaryTrie(void) {
	FILE *words;

	words = fopen("resources/words_alpha.txt", "r");
    root = getNode();

	if (words == NULL) {
		printf("Failed to open file.\n"); 
		perror("Error: ");
	} 

	while (!feof(words)) {
		char s[100];
        if (strcmp("m", s) == 0) printf("WTF\n");
        if (strcmp("monkey", s) == 0) printf("test\n");
		fscanf(words, "%s", s);
		insert(s);
	}

	fclose(words);
}