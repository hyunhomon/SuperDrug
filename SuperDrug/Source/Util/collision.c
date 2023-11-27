#include "../../Header/Util/pch.h"

int Collision_Check(SDL_Rect rect1, SDL_Rect rect2)
{
    if (rect1.x + rect1.w >= rect2.x &&
        rect1.x <= rect2.x + rect2.w &&
        rect1.y + rect1.h >= rect2.y &&
        rect1.y <= rect2.y + rect2.h) {
        return 1;
    }

    return 0;
}

int Collision_Check_With_Point(SDL_Rect rect, int x, int y)
{
    if (x >= rect.x && x <= rect.x + rect.w &&
        y >= rect.y && y <= rect.y + rect.h) {
        return 1;
    }

    return 0;
}
