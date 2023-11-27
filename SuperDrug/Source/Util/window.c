#include "../../Header/Util/pch.h"

SDL_Window* window = NULL;
SDL_Surface* renderer = NULL;

int Program_Init()
{
	// SDL Init
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		printf("Fail to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}

	// Image Init
	if (Image_Init() != 0) {
		SDL_Quit();
		return 1;
	}
	
	// Audio Init
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096)) {
		printf("Fail to initialize Audio: %s\n", Mix_GetError());
		Mix_Quit();
		SDL_Quit();
		return 1;
	}

	// Font Init
	if (TTF_Init() < 0) {
		printf("Fail to initialize Font: %s\n", TTF_GetError());
		TTF_Quit();
		SDL_Quit();
		return 1;
	}

	// Window Init
	window = SDL_CreateWindow(GAME_TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
	if(!window) {
		printf("Fail to initialize Window: %s\n", SDL_GetError());

		IMG_Quit();
		Mix_Quit();
		TTF_Quit();

		SDL_Quit();

		return 1;
	}

	// Renderer Init
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		printf("Fail to initialize Renderer: %s\n", SDL_GetError());

		IMG_Quit();
		Mix_Quit();
		TTF_Quit();

		SDL_DestroyWindow(window);
		SDL_Quit();

		return 1;
	}

	// Timer Init
	Timer_Init();

	// Random Init
	srand(time(NULL));

	return 0;
}

void Util_Update()
{
	Key_Update();
	Mouse_Update();

	Timer_Update();
}

SDL_Window* Get_Window()
{
	if (window == NULL) {
		printf("Fail to initialize Window");
		return NULL;
	}

	return window;
}

SDL_Surface* Get_Renderer()
{
	if (renderer == NULL) {
		printf("Fail to initialize Renderer");
		return NULL;
	}

	return renderer;
}

void Program_Release()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	IMG_Quit();
	Mix_Quit();
	TTF_Quit();

	SDL_Quit();
}
