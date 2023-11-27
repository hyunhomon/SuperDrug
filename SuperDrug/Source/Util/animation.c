#include "../../Header/Util/pch.h"

void Animation_Init(Animation* anim, int fps, int isLoop)
{
	List_Init(&anim->animList);

	anim->animTimer = 0.0;
	anim->fps = fps;
	anim->isLoop = isLoop;
	anim->end = 0;
	anim->currentFrame = 0;
}

void Animation_Update(Animation* anim, double dt)
{
	if (anim->end) return;

	anim->animTimer += dt;

	if (anim->animTimer >= 1.0 / anim->fps) {
		anim->animTimer = 0.0;
		anim->currentFrame++;

		if (anim->isLoop) {
			anim->currentFrame %= anim->animList.len;
		}
		else if (anim->currentFrame > anim->animList.len) {
			anim->end = 1;
			anim->currentFrame = anim->animList.len;
		}
	}
}

void Animation_Restart(Animation* anim)
{
	anim->animTimer = 0.0;
	anim->currentFrame = 0;
	anim->end = 0;
}

void Animation_Release(Animation* anim)
{
	List_Release(&anim->animList);
}

void Animation_Release_With_Texture(Animation* anim)
{
	Node* textureNode = anim->animList.head;

	for (int i = 0; i < anim->currentFrame; i++) {
		SDL_Texture* texture = (SDL_Texture*)textureNode->val;

		SDL_DestroyTexture(texture);

		textureNode = textureNode->next;
	}

	List_Release(&anim->animList);
}

void appendTexture(Animation* anim, SDL_Texture* texture)
{
	List_Push(&anim->animList, texture);
}

SDL_Texture* getCurrentFrame(Animation* anim)
{
	return (SDL_Texture*)List_Search(&anim->animList, anim->currentFrame);
}
