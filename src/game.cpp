#include "../include/game.h"



Game::Game() {
	std::cout << "Game began" << std::endl;
	isRunning = true;
}

Game::~Game() {
	// board = new Board(renderer);
}


void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullScreen) {

	int flags = 0;
	if (fullScreen) flags = SDL_WINDOW_FULLSCREEN;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "Subsystems Initialized..." << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		if (window) { // confirm window was created
			std::cout << "Window created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);

		if (renderer) { // confirm renderer was created
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer created" << std::endl;
		}

		isRunning = true;
	} else {
		isRunning = false;
	}

}

void Game::handleEvents() {
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				case SDLK_RETURN:
					break;
			}
		default:
			break;
	}
}



void Game::update() {



}


void Game::render() {
	SDL_RenderClear(renderer);
	// this is where we would add stuff to render
	SDL_RenderPresent(renderer);
}


void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game cleaned" << std::endl;
}


bool Game::running() {
	return isRunning;
}