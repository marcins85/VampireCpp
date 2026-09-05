// VampireCpp.cpp: definiuje punkt wejścia dla aplikacji.
//

#include "VampireCpp.h"
#include <SDL3/SDL.h>
#include <cmath>
#include <algorithm>

struct Entity
{
	float pos_x;
	float pos_y;
	float size_x;
	float size_y;
	float speed;
};

struct Player : Entity
{
	
};

struct Enemy : Entity
{
	
};

SDL_FRect makeRect(const Entity& entity)
{
	return SDL_FRect{ entity.pos_x, entity.pos_y, entity.size_x, entity.size_y };
}

void normalizeVector(float& x, float& y)
{
	if (x != 0.0f || y != 0.0f)
	{
		float dirLength = std::sqrt((x * x) + (y * y));
		x = x / dirLength;
		y = y / dirLength;
	}
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
	float playerSpeed = 100.0f;
	Player player{width / 2 - playerSizeX / 2, height / 2 - playerSizeY / 2, playerSizeX, playerSizeY, playerSpeed};

	float enemySizeX = 30.0f;
	float enemySizeY = 90.0f;
	float enemySpeed = 80.0f;
	Enemy enemy{20.0f, 100.0f, enemySizeX, enemySizeY, enemySpeed};

	int prevTime = SDL_GetTicks();
	int actualTime = 0;

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
		actualTime = SDL_GetTicks();
		float deltaTime = ((float)actualTime - (float)prevTime) / 1000;

		float dirX = 0.0f;
		float dirY = 0.0f;
		const bool* keyState = SDL_GetKeyboardState(nullptr);
		if (keyState[SDL_SCANCODE_A]) dirX = -1.0f;
		if (keyState[SDL_SCANCODE_D]) dirX = 1.0f;
		if (keyState[SDL_SCANCODE_S]) dirY = 1.0f;
		if (keyState[SDL_SCANCODE_W]) dirY = -1.0f;

		normalizeVector(dirX, dirY);

		player.pos_x += player.speed * dirX * deltaTime;
		player.pos_x = std::clamp(player.pos_x, 0.0f, width - player.size_x);

		player.pos_y += player.speed * dirY * deltaTime;
		player.pos_y = std::clamp(player.pos_y, 0.0f, height - player.size_y);
		
		float enemyDirX = player.pos_x - enemy.pos_x;
		float enemyDirY = player.pos_y - enemy.pos_y;
		normalizeVector(enemyDirX, enemyDirY);

		enemy.pos_x += enemy.speed * enemyDirX * deltaTime;
		enemy.pos_y += enemy.speed * enemyDirY * deltaTime;

		SDL_FRect playerRect = makeRect(player);
		SDL_FRect enemyRect = makeRect(enemy);

		//render
		SDL_SetRenderDrawColor(renderer, 20, 20, 20, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &playerRect);
		SDL_RenderFillRect(renderer, &enemyRect);
		SDL_RenderPresent(renderer);

		prevTime = actualTime;
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}
