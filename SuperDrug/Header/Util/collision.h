#pragma once

#include <SDL.h>

int Collision_Check(SDL_Rect rect1, SDL_Rect rect2);

int Collision_Check_With_Point(SDL_Rect rect, int x, int y);
