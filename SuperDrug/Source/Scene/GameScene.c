#include "../../Header/Util/pch.h"
#include "../../Header/Scene/GameScene.h"

typedef struct {
	int status;
} GameScene;

GameScene gameScene;

void GameScene_Init()
{
	SDL_Renderer* renderer = Get_Renderer();
}

void GameScene_Event()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			gameScene.status = EXIT_GAME;
			break;
		}
	}
}

void GameScene_Update()
{
	double dt = getDeltaTime();

	int mouseX = 0, mouseY = 0;
	getCurrentMousePos(&mouseX, &mouseY);
}

void GameScene_Render()
{
	SDL_Renderer* renderer = Get_Renderer();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}

void GameScene_Release()
{
}

int GameScene_Loop()
{
	gameScene.status = SCENE_LOOP;

	while (gameScene.status == SCENE_LOOP) {
		Util_Update();

		GameScene_Event();
		GameScene_Update();
		GameScene_Render();
	}

	return gameScene.status;
}
