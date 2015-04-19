#include "Game.h"
#include <ctime>

int main(int argc, char* args[]) {
	srand(time(0));

	Game game(720, 480);

	game.run();

	return EXIT_SUCCESS;
}