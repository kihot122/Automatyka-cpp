#pragma once
#include "SDL.h"
#include "shared.hpp"

struct Window
{
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	SDL_Event E;
	int width, height;
	
	Window(int width, int height);
	Vec2<int> Translate(Vec2<double>& v);
	void Clear();
	void Update(World &world);
	void Events();
};