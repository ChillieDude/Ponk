#include "mBall.h"
#include <iostream>
#include <cstdlib>

mBall::mBall(int x, int y, bool ml, bool mu, const int SCREEN_W, const int SCREEN_H) : moving_left(ml), moving_up(mu), velX(0.0), velUp(0.0), velDown(0.0), dOff(0.0), SCREEN_H(SCREEN_H), SCREEN_W(SCREEN_W), BALL_X(x), BALL_Y(y) {
	ball.x = x;
	ball.y = y;
	ball.w = 10;
	ball.h = 10;

	dOff = rand() % 100;
}

void mBall::draw(SDL_Renderer* r) {
	SDL_SetRenderDrawColor(r, 255, 255, 255, 255);

	SDL_RenderFillRect(r, &ball);
}

bool mBall::movingLeft() {
	return moving_left;
}

bool mBall::movingUp() {
	return moving_up;
}

int mBall::getWidth() {
	return ball.w;
}

int mBall::getHeight() {
	return ball.h;
}

int mBall::getX() {
	return ball.x;
}

int mBall::getY() {
	return ball.y;
}

void mBall::reset(bool ml, bool mu) {
	ball.x = BALL_X;
	ball.y = BALL_Y;
	moving_left = ml;
	moving_up = mu;

	dOff = rand() % 100;
}

int mBall::getXSpeed() {
	return xIncrease;
}

int mBall::getYSpeed() {
	return yIncrease;
}

void mBall::update(Paddle& p1, Paddle& p2, float delta, float speed, int& pWins, int& cWins) {
	if(ball.x <= p1.getX()+p1.getWidth() && ball.y + ball.h >= p1.getY() && ball.y <= p1.getY() + p1.getHeight()) {
		moving_left = false;
		float force = p1.getForce();
		moving_up = (force >= 0 ? false : true);

		if(moving_up) force = -force;

		dOff = (float) (50.0f + (rand() % 100)) * force;
		xIncrease = speed * delta;
		yIncrease = (dOff * delta <= 0 ? 1 : dOff * delta);
	} else if(ball.x + ball.w >= p2.getX() && ball.y + ball.h >= p2.getY() && ball.y <= p2.getY() + p2.getHeight()) {
		moving_left = true;
		float force = p2.getForce();
		moving_up = (force >= 0 ? false : true);

		if(moving_up) force = -force;

		dOff = (float) (50.0f + (rand() % 100)) * force;
		xIncrease = speed * delta;
		yIncrease = (dOff * delta <= 0 ? 1 : dOff * delta);
	}

	if(ball.y <= 0) {
		moving_up = !moving_up;
		velUp = 0;
		ball.y += 1;
	} else if(ball.y + ball.h >= SCREEN_H) {
		moving_up = !moving_up;
		velDown = 0;
		ball.y -= 1;
	} else if(ball.x + ball.w >= SCREEN_W) {
		pWins++;
	} else if(ball.x <= 0) {
		cWins++;
	}

	move(speed, delta);
}

void mBall::move(float speed, float delta) {
	if(movingUp()) {
		velUp -= dOff * delta;

		if(velUp <= -1) {
			ball.y += velUp;
			velUp = 0;
		}
	} else {
		velDown += dOff * delta;
		
		if(velDown >= 1) {
			ball.y += velDown+1;
			velDown = 0;
		}
	}

	if(movingLeft()) {
		velX -= speed * delta;
		if(velX <= -1) {
			ball.x += velX;
			velX = 0;
		}
	} else {
		velX += speed * delta;
		if(velX >= 1) {
			ball.x += velX;
			velX = 0;
		}
	}
}