#include "../../Header/Util/pch.h"

size_t memSize = sizeof(Uint8) * SDL_NUM_SCANCODES;

const Uint8 beforeKeyState[SDL_NUM_SCANCODES];
const Uint8* currentKeyState = NULL;

int beforeMousePosX = 0;
int beforeMousePosY = 0;
Uint32 beforeMouseState = 0;

int currentMousePosX = 0;
int currentMousePosY = 0;
Uint32 currentMouseState = 0;

void Key_Update()
{
	if (currentKeyState == NULL) {
		currentKeyState = SDL_GetKeyboardState(NULL);
	}

	SDL_memcpy(beforeKeyState, currentKeyState, memSize);
}

int getKeyState(int keyCode)
{
	if (beforeKeyState[keyCode] == 0 && currentKeyState[keyCode] == 0)
		return KEY_NONE;
	if (beforeKeyState[keyCode] == 0 && currentKeyState[keyCode] == 1)
		return KEY_DOWN;
	if (beforeKeyState[keyCode] == 1 && currentKeyState[keyCode] == 0)
		return KEY_UP;
	if (beforeKeyState[keyCode] == 1 && currentKeyState[keyCode] == 1)
		return KEY_HOLD;
}

int getButtonState(int buttonCode)
{
	Uint32 buttonMask = SDL_BUTTON(buttonCode);

	int before = beforeMouseState & buttonMask;
	int current = currentMouseState & buttonMask;

	if (before == 0 && current == 0)
		return KEY_NONE;
	if (before == 0 && current == 1)
		return KEY_DOWN;
	if (before == 1 && current == 0)
		return KEY_UP;
	if (before == 1 && current == 1)
		return KEY_HOLD;
}

void Mouse_Update()
{
	beforeMousePosX = currentMousePosX;
	beforeMousePosY = currentMousePosY;

	beforeMouseState = currentMouseState;
	currentMouseState = SDL_GetMouseState(&currentMousePosX, &currentMousePosY);
}

void getBeforeMousePos(int* beforePosX, int* beforePosY)
{
	if (beforePosX != NULL)
		*beforePosX = beforeMousePosX;
	if (beforePosY != NULL)
		*beforePosY = beforeMousePosY;
}

void getCurrentMousePos(int* currentPosX, int* currentPosY)
{
	if (currentPosX != NULL)
		*currentPosX = currentMousePosX;
	if (currentPosY != NULL)
		*currentPosY = currentMousePosY;
}

void getDeltaMousePos(int* deltaPosX, int* deltaPosY)
{
	if (deltaPosX != NULL)
		*deltaPosX = currentMousePosX - beforeMousePosX;
	if (deltaPosY != NULL)
		*deltaPosY = currentMousePosY - beforeMousePosY;
}
