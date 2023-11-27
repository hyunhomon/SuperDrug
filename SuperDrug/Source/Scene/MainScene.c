#include "../../Header/Util/pch.h"
#include "../../Header/Scene/MainScene.h"

typedef struct {
	int status;

	SDL_Texture* img_bg;
	SDL_Texture* img_logo;
	SDL_Texture* img_start;

	SDL_Rect rect_logo;
	SDL_Rect rect_start;

} MainScene;

MainScene mainScene;

void MainScene_Init()
{
	SDL_Renderer* renderer = Get_Renderer();

	mainScene.img_bg = Image_Load(renderer, "./Asset/Image/Background/Background.png");
	mainScene.img_logo = Image_Load(renderer, "./Asset/Image/Logo/Logo.png");
	mainScene.img_start = Image_Load(renderer, "./Asset/Image/Background/start.png");

	getImageSize(mainScene.img_logo, &mainScene.rect_logo.w, &mainScene.rect_logo.h);
	mainScene.rect_logo.x = 540.0;
	mainScene.rect_logo.y = 100.0;

	getImageSize(mainScene.img_start, &mainScene.rect_start.w, &mainScene.rect_start.h);
	mainScene.rect_start.x = 411;
	mainScene.rect_start.y = 531;
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

	if (getButtonState(SDL_BUTTON_LEFT) == KEY_DOWN) {
		if (Collision_Check_With_Point(mainScene.rect_logo, mouseX, mouseY)) {
			printf("차수현의 현호를 찾아서 발표가 이후에 이어질 예정입니다.");
			mainScene.status = EXIT_GAME;
		}
		if (Collision_Check_With_Point(mainScene.rect_start, mouseX, mouseY)) {
			printf("GAME START!\n");
			mainScene.status = GAME_SCENE;
		}
	}

	if (getKeyState(SDL_SCANCODE_SPACE) == KEY_DOWN) {
		printf("GAME START!\n");
		mainScene.status = GAME_SCENE;
	}
	if (getKeyState(SDL_SCANCODE_ESCAPE) == KEY_DOWN) {
		printf("EXIT!\n");
		mainScene.status = EXIT_GAME;
	}
}

void MainScene_Render()
{
	SDL_Renderer* renderer = Get_Renderer();

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	Image_Draw(renderer, 0, 0, mainScene.img_bg);
	Image_Draw(renderer, mainScene.rect_logo.x, mainScene.rect_logo.y, mainScene.img_logo);
	Image_Draw(renderer, mainScene.rect_start.x, mainScene.rect_start.y, mainScene.img_start);

	SDL_RenderPresent(renderer);
}

void MainScene_Release()
{
	SDL_DestroyTexture(mainScene.img_bg);
	SDL_DestroyTexture(mainScene.img_logo);
	SDL_DestroyTexture(mainScene.img_start);
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
