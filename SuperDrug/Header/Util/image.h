#pragma once

#include <SDL_image.h>

int Image_Init();

SDL_Texture* Image_Load(SDL_Renderer* renderer, const char* file);

void Image_Draw(SDL_Renderer* renderer, int x, int y, SDL_Texture* texture);

void Image_Draw_With_Ratio(SDL_Renderer* renderer, int x, int y, double widthRatio, double heightRatio, SDL_Texture* texture);

void Image_Draw_With_Rect(SDL_Renderer* renderer, SDL_Rect* rect, SDL_Texture* texture);

void getImageSize(SDL_Texture* texture, int* w, int* h);
