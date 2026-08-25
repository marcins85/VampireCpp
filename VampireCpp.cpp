// VampireCpp.cpp: definiuje punkt wejścia dla aplikacji.
//

#include "VampireCpp.h"
#include <SDL3/SDL.h>

using namespace std;

struct Player
{
	float pos_x;
	float pos_y;
	float size_x;
	float size_y;
};

SDL_FRect makeRect(const Player& player)
{
	return SDL_FRect{ player.pos_x, player.pos_y, player.size_x, player.size_y };
}

int main()
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	int width = 1280;
	int height = 720;

	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("Coludn't initialize SDL: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (!SDL_CreateWindowAndRenderer("VampireCpp", width, height, SDL_WINDOW_RESIZABLE, &window, &renderer))
	{
		SDL_Log("Coludn't initialize window/renderer: %s", SDL_GetError());
		return SDL_APP_FAILURE;
	}
	
	SDL_Event event;
	float playerSizeX = 40;
	float playerSizeY = 100;
	Player player{width / 2 - playerSizeX / 2, height / 2 - playerSizeY / 2, playerSizeX, playerSizeY};

	

	bool running = true;
	while (running)
	{
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT)
			{
				running = false;
			}
		}

		//update
		player.pos_x += 0.1f;
		SDL_FRect playerRect = makeRect(player);
		

		//render
		SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &playerRect);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
