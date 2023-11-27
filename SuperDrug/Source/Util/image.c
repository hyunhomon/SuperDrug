#include "../../Header/Util/pch.h"

int Image_Init()
{
	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;

	if (!(IMG_Init(imgFlags) & imgFlags)) {
		printf("Fail to initialize Image: %s\n", IMG_GetError());
		return -1;
	}

	return 0;
}

SDL_Texture* Image_Load(SDL_Renderer* renderer, const char* file)
{
	SDL_Surface* surface;
	SDL_Texture* texture;

	surface = IMG_Load(file);

	if (surface == NULL) {
		printf("Fail to load File: %s\n", file);
		return NULL;
	}

	texture = SDL_CreateTextureFromSurface(renderer, surface);

	if (texture == NULL) {
		printf("Fail to generate Texture\n");
	}

	SDL_FreeSurface(surface);

	return texture;
}

void Image_Draw(SDL_Renderer* renderer, int x, int y, SDL_Texture* texture)
{
	SDL_Rect src;
	SDL_Rect dst;

	src.x = 0;
	src.y = 0;

	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);

	dst.x = x;
	dst.y = y;

	dst.w = src.w;
	dst.h = src.h;

	SDL_RenderCopy(renderer, texture, NULL, &dst);
}

void Image_Draw_With_Ratio(SDL_Renderer* renderer, int x, int y, double widthRatio, double heightRatio, SDL_Texture* texture)
{
	SDL_Rect src;
	SDL_Rect dst;

	src.x = 0;
	src.y = 0;
	
	SDL_QueryTexture(texture, NULL, NULL, &src.w, &src.h);

	dst.x = x;
	dst.y = y;

	dst.w = (int)(src.w * widthRatio);
	dst.h = (int)(src.h * heightRatio);

	SDL_RenderCopy(renderer, texture, NULL, &dst);
}

void Image_Draw_With_Rect(SDL_Renderer* renderer, SDL_Rect* rect, SDL_Texture* texture)
{
	SDL_RenderCopy(renderer, texture, NULL, rect);
}

void getImageSize(SDL_Texture* texture, int* w, int* h)
{
	SDL_QueryTexture(texture, NULL, NULL, w, h);
}
