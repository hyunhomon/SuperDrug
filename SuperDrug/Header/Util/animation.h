#pragma once

#include <SDL_image.h>
#include "linkedlist.h"

#define ANIM_LOOP_OFF 0
#define ANIM_LOOP_ON 1

typedef struct {
	List animList;
	double animTimer;

	int currentFrame;
	int fps;
	int isLoop;
	int end;
} Animation;

void Animation_Init(Animation* anim, int fps, int isLoop);

void Animation_Update(Animation* anim, double dt);

void Animation_Restart(Animation* anim);

void Animation_Release(Animation* anim);

void Animation_Release_With_Texture(Animation* anim);

void appendTexture(Animation* anim, SDL_Texture* texture);

SDL_Texture* getCurrentFrame(Animation* anim);
