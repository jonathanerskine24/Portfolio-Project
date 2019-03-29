#include "../include/scoring.h"

// calculates score for a simple string
// can be used for calculating words that are not the main word

// fix weird compilation error

// might need to add double and triple word or letters
// for now, it works
int CalculateScore(char *s) { 
    int len = strlen(s);
    int score = 0;
    for (int i = 0; i < len; i++) {
        score = score + (scores[s[i] - 97]);
    }
    return score;
}