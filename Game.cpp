#include "Game.h"
#include "Pong.h"

Game::Game(int w, int h) : SCREEN_W(w), SCREEN_H(h), running(false) {}

Game::~Game() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	window = nullptr;
	renderer = nullptr;

	SDL_Quit();
}

void Game::run() {
	if(!init()) {
		std::cout << "Failed to initialize game: " << SDL_GetError() << std::endl;
		return;
	}
	running = true;
	play();
}

bool Game::isRunning() {
	return running;
}

bool Game::init() {
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		return false;
	}

	window = SDL_CreateWindow("Ponk", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);

	if(!window) {
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	if(!renderer) {
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	return true;
}

void Game::play() {
	SDL_Event e;

	int pong_width = 15, pong_height = SCREEN_H / 4;
	int padding = 10;

	Pong m_pongLeft(padding, SCREEN_H/2-(pong_height/2), pong_width, pong_height, SCREEN_H);
	Pong m_pongRight(SCREEN_W-(pong_width+padding), SCREEN_H/2-(pong_height/2), pong_width, pong_height, SCREEN_H);
	
	Uint32 curTime = SDL_GetTicks(), lastTime;
	float delta = 0;

	const Uint8 *state = SDL_GetKeyboardState(NULL);

	float speed = SCREEN_H / 3;

	while(isRunning()) {
		lastTime = curTime;
		curTime = SDL_GetTicks();
		delta = (float) ((curTime - lastTime) / 1000.f);

		if(state[SDL_SCANCODE_W]) {
			m_pongLeft.moveUp(speed * delta);
		} else if(state[SDL_SCANCODE_S]) {
			m_pongLeft.moveDown(speed * delta);
		}
		if(state[SDL_SCANCODE_UP]) {
			m_pongRight.moveUp(speed * delta);
		} else if(state[SDL_SCANCODE_DOWN]) {
			m_pongRight.moveDown(speed * delta);
		}

		while(SDL_PollEvent(&e) != 0) {
			switch(e.type) {
				case SDL_QUIT:
					running = false;
					break;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		m_pongLeft.draw(renderer);
		m_pongRight.draw(renderer);

		SDL_RenderPresent(renderer);
	}
}