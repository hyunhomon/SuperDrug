#pragma once

#define KEY_HOLD -1
#define KEY_DOWN 0
#define KEY_UP 1
#define KEY_NONE 2

void Key_Update();

int getKeyState(int keyCode);

int getButtonState(int buttonCode);

void Mouse_Update();

void getBeforeMousePos(int* beforePosX, int* beforePosY);

void getCurrentMousePos(int* currentPosX, int* currentPosY);

void getDeltaMousePos(int* deltaPosX, int* deltaPosY);
