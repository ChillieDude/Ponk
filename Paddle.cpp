#include "Paddle.h"
#include <iostream>

Paddle::Paddle(int x, int y, int w, int h, const int sh) : SCREEN_H(sh), velUp(0.0), velDown(0.0), force(0.0) {
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}

void Paddle::moveUp(float vel) {
	if(rect.y <= 0) return;
	if(force > 0) force = 0;

	velUp -= vel;
	if(force >= -1)
		force -= vel;

	float temp = -velUp;
	if((int)temp > 0) {
		rect.y -= temp;
		velUp = 0;
	}
}

void Paddle::moveDown(float vel) {
	if(rect.y + rect.h >= SCREEN_H) return;
	if(force < 0) force = 0;

	velDown += vel;
	if(force <= 1)
		force += vel;

	if((int) velDown > 0) {
		rect.y += velDown+1;
		velDown = 0;
	}


}

void Paddle::setPosition(int x, int y) {
	rect.x = x;
	rect.y = y;
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