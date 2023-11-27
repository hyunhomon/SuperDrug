#pragma once

#include <SDL.h>

#define GAME_TITLE "SuperDrug"

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#define SCENE_LOOP -2
#define EXIT_GAME -1

#define MAIN_SCENE 0
#define GAME_SCENE 1

int Program_Init();

void Util_Update();

SDL_Window* Get_Window();

SDL_Surface* Get_Renderer();

void Program_Release();
