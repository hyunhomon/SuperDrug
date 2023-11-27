#include "../../Header/Util/pch.h"
#include "../../Header/Scene/MainScene.h"

typedef struct {
	int status;

	SDL_Texture* img_logo;

	SDL_Rect rect_logo;

} MainScene;

MainScene mainScene;

void MainScene_Init()
{
	SDL_Renderer* renderer = Get_Renderer();
}

void MainScene_Event()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			mainScene.status = EXIT_GAME;
			break;
		}
	}
}

void MainScene_Update()
{
	double dt = getDeltaTime();

	int mouseX = 0, mouseY = 0;
	getCurrentMousePos(&mouseX, &mouseY);
}

void MainScene_Render()
{
	SDL_Renderer* renderer = Get_Renderer();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	SDL_RenderPresent(renderer);
}

void MainScene_Release()
{
}

int MainScene_Loop()
{
	mainScene.status = SCENE_LOOP;

	while (mainScene.status == SCENE_LOOP) {
		Util_Update();

		MainScene_Event();
		MainScene_Update();
		MainScene_Render();
	}

	return mainScene.status;
}
