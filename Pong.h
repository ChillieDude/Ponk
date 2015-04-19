#ifndef PONG_H
#define PONG_H

#include <SDL.h>

class Pong {
public:
	Pong(int x, int y, int width, int height, const int screen_height);
	~Pong();
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	void draw(SDL_Renderer*);
	void moveDown(float vel);
	void moveUp(float vel);
private:
	int x, y, width, height;
	float velY;
	const int SCREEN_H;
	SDL_Rect rect;
};

#endif