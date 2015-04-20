#include "Paddle.h"
#include <iostream>

Paddle::Paddle(int x, int y, int w, int h, const int sh) : SCREEN_H(sh), velY(0.0), force(0.0) {
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}

Paddle::~Paddle() {

}

void Paddle::moveUp(float vel) {
	if(rect.y <= 0) return;
	if(velY >= 0) velY = 0;
	if(force > 0) force = 0;

	velY -= vel;
	if(force >= -1)
		force -= vel;

	if(velY <= -1) {
		rect.y += velY;
		velY = 0;
	}
}

void Paddle::moveDown(float vel) {
	if(rect.y + rect.h >= SCREEN_H) return;
	if(velY <= 0) velY = 0;
	if(force < 0) force = 0;

	velY += vel;
	if(force <= 1)
		force += vel;

	if(velY >= 1) {
		rect.y += velY*2;
		velY = 0;
	}
}

void Paddle::draw(SDL_Renderer* r) {
	SDL_SetRenderDrawColor(r, 255, 255, 255, 255);

	SDL_RenderFillRect(r, &rect);
}

int Paddle::getX() {
	return rect.x;
}

int Paddle::getY() {
	return rect.y;
}

int Paddle::getWidth() {
	return rect.w;
}

int Paddle::getHeight() {
	return rect.h;
}

float Paddle::getForce() {
	return force;
}