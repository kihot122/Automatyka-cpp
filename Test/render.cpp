#include "render.hpp"

Window::Window(int width, int height) : width(width), height(height)
{
	SDL_Init(SDL_INIT_VIDEO);
	mWindow = SDL_CreateWindow("Symulacja", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
	Clear();
}

Vec2<int> Window::Translate(Vec2<double>& v)
{
	return Vec2<int>(int((v.x + 128) * width / 256), int(height - (128 + v.y) * height / 256));
}

void Window::Clear() 
{
	SDL_RenderClear(mRenderer);
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_RenderFillRect(mRenderer, NULL);
	SDL_RenderPresent(mRenderer);
}

void Window::Update(World& world) 
{
	for (Bullet& bullet : world.Bullets)
	{
		SDL_SetRenderDrawColor(mRenderer, bullet.color, bullet.color >> 8, bullet.color >> 16, bullet.color >> 24);
		SDL_RenderDrawPoint(mRenderer, Translate(bullet.Pos).x, Translate(bullet.Pos).y);
	}
	SDL_RenderPresent(mRenderer);
}

void Window::Events()
{
	while (SDL_PollEvent(&E))
	{
		if (E.type == SDL_WINDOWEVENT && E.window.event == SDL_WINDOWEVENT_CLOSE)
			exit(0);
	}
}
