#include "Pong.h"
#include <iostream>

Pong::Pong(int x, int y, int w, int h, const int sh) : x(x), y(y), width(w), height(h), SCREEN_H(sh), velY(0.0) {
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;
}

Pong::~Pong() {

}

//speed difference between moving up & down

void Pong::moveUp(float vel) {
	if(rect.y <= 0) return;
	if(velY >= 0) velY = 0;

	velY -= vel;

	if(velY <= -1) {
		rect.y += velY;
		velY = 0;
	}
}

void Pong::moveDown(float vel) {
	if(rect.y + height >= SCREEN_H) return;
	if(velY <= 0) velY = 0;

	velY += vel;

	if(velY >= 1) {
		rect.y += velY*2;
		velY = 0;
	}
}

void Pong::draw(SDL_Renderer* r) {
	SDL_SetRenderDrawColor(r, 255, 255, 255, 255);

	SDL_RenderFillRect(r, &rect);
}