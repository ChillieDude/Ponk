#include "Game.h"
#include <ctime>

int main(int argc, char* args[]) {
	srand(time(0));

	Game game(800, 600);

	game.run();

	return EXIT_SUCCESS;
}