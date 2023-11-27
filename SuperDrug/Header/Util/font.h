#pragma once

#include <SDL_ttf.h>

void Text_Draw(SDL_Renderer* renderer, TTF_Font* font, const char* str, int x, int y, SDL_Color c);

void Text_Draw_Center(SDL_Renderer* renderer, TTF_Font* font, const char* str, int x, int y, SDL_Color c);

void Text_Draw_Center_With_Ratio(SDL_Renderer* renderer, TTF_Font* font, const char* str, int x, int y, SDL_Color c, double ratio_x, double ratio_y);
