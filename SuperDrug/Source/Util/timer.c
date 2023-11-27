#include "../../Header/Util/pch.h"

Uint64 beforeTicks;
Uint64 currentTicks;
Uint64 elapsedTicks;
double deltaTime;

void Timer_Init()
{
	beforeTicks = SDL_GetPerformanceCounter();
	currentTicks = SDL_GetPerformanceCounter();
	elapsedTicks = 0;
	deltaTime = 0;
}

void Timer_Update()
{
	beforeTicks = currentTicks;
	currentTicks = SDL_GetPerformanceCounter();
	elapsedTicks = currentTicks - beforeTicks;
	deltaTime = (double)elapsedTicks / SDL_GetPerformanceFrequency();
}

double getDeltaTime()
{
	return deltaTime;
}
