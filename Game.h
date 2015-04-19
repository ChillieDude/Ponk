#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <iostream>

class Game {
public:
	Game(int width, int height);
	~Game();
	void run();
	const int getWindowWidth();
	const int getWindowHeight();
	int getPlayerWins();
	int getComputerWins();
private:
	void play();
	bool init();
	bool isRunning();

	bool running;
	const int SCREEN_W, SCREEN_H;
	int pWins, cWins;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif