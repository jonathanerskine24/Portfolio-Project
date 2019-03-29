#include "../include/helper.h"
#include "../include/types.h"
// #include "../include/hash.h"
#include "../include/trie.h"

int ConvertXYtoIndex(int x, int y) {
	return ((y * BOARD_SIZE) + (x));
}

void append(char *s, char c) {
    int len = strlen(s);
    s[len] = c;
    s[len+1] = '\0';
    return;
}

Position GetMousePos(SDL_Event e) {
	Position p;
	p.x = e.button.x;
	p.y = e.button.y;
	return p;
}

bool CheckClick(Position pos, SDL_Rect r) {
	if (pos.x < r.x) return false;
	else if (pos.y < r.y) return false;
	else if (pos.x > r.x + r.w) return false;
	else if (pos.y > r.y + r.h) return false;
	else return true;
}

int findLow(StagedTile *st[], bool direction) {
	int low = 0;
	if (direction == VERTICAL) {
		low = st[0]->y_pos;
		for (int i = 0; i < 7; i ++) {
			if (st[i] == NULL) break;
			if (st[i]->y_pos < low) low = st[i]->y_pos;
		}
	} else {
		low = st[0]->x_pos;
		for (int i = 0; i < 7; i ++) {
			if (st[i] == NULL) break;
			if (st[i]->x_pos < low) low = st[i]->x_pos;
		}
	}
	return low;
}

int findHigh(StagedTile *st[], bool direction) {
	int high = 0;
	if (direction == VERTICAL) {
		high = st[0]->y_pos;
		for (int i = 0; i < 7; i ++) {
			if (st[i] == NULL) break;
			if (st[i]->y_pos > high) high = st[i]->y_pos;
		}
	} else {
		high = st[0]->x_pos;
		for (int i = 0; i < 7; i ++) {
			if (st[i] == NULL) break;
			if (st[i]->x_pos > high) high = st[i]->x_pos;
		}
	}
	return high;
}

int SelectTile() {
	int randomWeight = rand() % numTilesRemaining;
	int selectedLetter;
	for (int i = 0; i < 26; i++) {
		if (tileBag[i] != 0) {
			randomWeight = randomWeight - tileBag[i];
			if (randomWeight <= 0) {
				selectedLetter = i;
				tileBag[i]--;
				numTilesRemaining--;
				break;
			}
		}
	}
	return selectedLetter;
}