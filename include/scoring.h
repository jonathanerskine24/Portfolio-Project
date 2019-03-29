#pragma once
#include "types.h"

static int scores[26] = {
    1, // A
    3, // B
    3, // C
    2, // D
    1, // E
    4, // F
    2, // G
    3, // H
    1, // I
    8, // J
    5, // K
    2, // L
    4, // M
    2, // N
    1, // O
    3, // P
    10,// Q
    1, // R
    1, // S
    1, // T
    2, // U
    5, // V
    4, // W
    8, // X
    3, // Y
    10// Z
};


int CalculateScore(char *s);
