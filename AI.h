#ifndef AI_H
#define AI_H

#include "mBall.h"

enum Difficulty {
	EASY,
	MEDIUM,
	HARD
};

class AI {
public:
	AI(const int SCREEN_WIDTH, const int SCREEN_HEIGHT, Difficulty difficulty);
	AI(const int SCREEN_WIDTH, const int SCREEN_HEIGHT);
	void update(Paddle& paddle, mBall& ball, float speed);
private:
	Difficulty difficulty;
	const int SCREEN_W, SCREEN_H;
};

#endif