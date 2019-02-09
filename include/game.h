#pragma once
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
// #include "../include/piece.h"
// #include "../include/board.h"
// 


class Game {
	private:
		SDL_Window *window;
		SDL_Renderer *renderer;
		bool isRunning;
	public:
		Game();
		~Game();
		void init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen);
		void handleEvents();
		void update();
		void render();
		void clean();
		bool running();
		// bool began();
		// // void renderMenu();
		// // void Reset();

};