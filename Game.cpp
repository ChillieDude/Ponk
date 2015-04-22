#include "Game.h"
#include "AI.h"
#include "Paddle.h"
#include "mBall.h"
#include <cstdlib>

Game::Game(int w, int h) : SCREEN_W(w), SCREEN_H(h), running(false), pWins(0), cWins(0) {}

Game::~Game() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	window = nullptr;
	renderer = nullptr;

	SDL_Quit();
}

const int Game::getWindowWidth() {
	return SCREEN_W;
}

const int Game::getWindowHeight() {
	return SCREEN_H;
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

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if(!renderer) {
		return false;
	}

	return true;
}

void Game::play() {
	SDL_Event e;

	int pong_width = 15, pong_height = SCREEN_H / 4;
	int padding = 10;

	Paddle m_paddleLeft(padding, SCREEN_H/2-(pong_height/2), pong_width, pong_height, SCREEN_H);
	Paddle m_paddleRight(SCREEN_W-(pong_width+padding), SCREEN_H/2-(pong_height/2), pong_width, pong_height, SCREEN_H);
	mBall m_ball(SCREEN_W/2-5, SCREEN_H/2-5, (rand() % 2 == 0 ? false : true), (rand() % 2 == 0 ? false : true), SCREEN_W, SCREEN_H);

	Uint32 curTime, lastTime = SDL_GetTicks(), passed;

	const Uint8 *state = SDL_GetKeyboardState(NULL);

	float speed = SCREEN_H / 3;

	AI ai(SCREEN_W, SCREEN_H, EASY);

	while(isRunning()) {
		curTime = SDL_GetTicks();
		passed = curTime - lastTime;

		if(passed > 0) {
			lastTime = curTime;

			float delta = passed / 1000.0f;

			if(state[SDL_SCANCODE_W]) {
				m_paddleLeft.moveUp(speed * delta);
			} else if(state[SDL_SCANCODE_S]) {
				m_paddleLeft.moveDown(speed * delta);
			}

			int temp_p = pWins, temp_c = cWins;

			m_ball.update(m_paddleLeft, m_paddleRight, delta, SCREEN_H, pWins, cWins);

			if(temp_p != pWins || temp_c != cWins) {
				m_ball.reset((rand() % 2 == 0 ? false : true), (rand() % 2 == 0 ? false : true));
			}

			ai.update(m_paddleRight, m_ball, speed * delta);
		}
		while(SDL_PollEvent(&e) != 0) {
			switch(e.type) {
				case SDL_QUIT:
					running = false;
					break;
				case SDL_KEYDOWN:
					switch(e.key.keysym.sym) {
						case SDLK_ESCAPE:
							running = false;
							break;
					}
					break;
			}
		}

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		m_paddleLeft.draw(renderer);
		m_paddleRight.draw(renderer);
		m_ball.draw(renderer);

		SDL_RenderPresent(renderer);
	}
}