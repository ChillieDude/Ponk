#include "Ai.h"
#include <iostream>

AI::AI(const int w, const int h, Difficulty d) : difficulty(d), SCREEN_W(w), SCREEN_H(h) {}

AI::AI(const int w, const int h) : difficulty(EASY), SCREEN_W(w), SCREEN_H(h) {}

void AI::update(Paddle& paddle, mBall& ball, float speed) {
	int middle = paddle.getY()+(paddle.getHeight()/2);

	if(ball.movingLeft()) {
		if(difficulty == HARD) {
			if(middle < SCREEN_H / 2 && ((SCREEN_H/2) - middle > 2))
				paddle.moveDown(speed);
			else if(middle > SCREEN_H / 2 && (middle - (SCREEN_H/2) > 0))
				paddle.moveUp(speed);
		}
		return;
	}

	int xS = ball.getXSpeed()+1, yS = ball.getYSpeed();

	int xTurns = ((SCREEN_W-ball.getX()) / xS);
	xTurns = (xTurns < 0 ? 0 : xTurns);

	int yTurns = -1;

	bool bouncing = false;
	bool floor = false;
	int eX = -1, eY = -1;

	for(int i = 1;i <= xTurns;i++) {
		int temp = yS * i;

		if(ball.movingUp()) {
			if(ball.getY() - temp <= 0) {
				xTurns = i;
				yTurns = i;
				eX = ball.getX() + (xTurns*xS);
				eY = 0;
				bouncing = true;
				break;
			}
		} else {
			if((ball.getY()+ball.getHeight()) + temp >= SCREEN_H) {
				xTurns = i;
				yTurns = i;
				eX = ball.getX() + (xTurns*xS);
				eY = SCREEN_H-ball.getHeight();
				bouncing = true;
				floor = true;
				break;
			}
		}
		if(i == xTurns) {
			if(ball.movingUp())
				eY = ball.getY() - temp;
			else
				eY = ball.getY() + temp;

			eX = SCREEN_W-ball.getWidth();
			bouncing = false;
			yTurns = 0;
		}
	}

	if(eX == -1 || eY == -1 || yTurns == -1) return;
	eX = (eX >= SCREEN_W ? SCREEN_W-ball.getWidth() : eX);

	int distort = 0;

	switch(difficulty) {
		case EASY:
			distort = 5;
			break;
		case MEDIUM:
			distort = 4;
			break;
		case HARD:
			distort = 3;
			break;
	}
	if(ball.movingUp()) {
		eY += distort * 15;
	} else {
		eY -= distort * 15;
	}

	if(middle < eY && (paddle.getY()+paddle.getHeight()) < SCREEN_H-speed && (eY - middle > 2)) {
		paddle.moveDown(speed);
	} else if(middle > eY && paddle.getY() > 0&& (middle - eY > 2)) {
		paddle.moveUp(speed);
	}
}