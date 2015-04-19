#ifndef PONG_H
#define PONG_H

#include <SDL.h>

class Paddle {
public:
	Paddle(int x, int y, int width, int height, const int screen_height);
	~Paddle();
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	float getForce();
	void draw(SDL_Renderer*);
	void moveDown(float vel);
	void moveUp(float vel);
private:
	float velY, force;
	const int SCREEN_H;
	SDL_Rect rect;
};

#endif