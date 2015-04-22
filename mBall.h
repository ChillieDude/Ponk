#ifndef MBALL_H
#define MBALL_H

#include <SDL.h>
#include "Paddle.h"

class mBall {
public:
	mBall(int x, int y, bool move_left, bool move_up, const int SCREEN_W, const int SCREEN_H);
	void draw(SDL_Renderer* renderer);
	void update(Paddle& p1, Paddle& p2, float delta, float speed, int& player_wins, int& computer_wins);
	void reset(bool move_left, bool move_up);
	int getWidth();
	int getHeight();
	int getX();
	int getY();
	int getXSpeed();
	int getYSpeed();
	bool movingLeft();
	bool movingUp();
private:
	void move(float delta, float speed);

	SDL_Rect ball;
	float velX, velUp, velDown, dOff;
	int yIncrease, xIncrease;
	const int SCREEN_H, SCREEN_W, BALL_X, BALL_Y;
	bool moving_left, moving_up;
};

#endif