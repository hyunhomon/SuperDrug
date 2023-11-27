#include "../../Header/Util/pch.h"

void Text_Draw(SDL_Renderer* renderer, TTF_Font* font, const char* str, int x, int y, SDL_Color c)
{
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, str, c);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect r = { x, y, surface->w, surface->h };

    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &r);

    SDL_DestroyTexture(texture);
}

void Text_Draw_Center(SDL_Renderer* renderer, TTF_Font* font, const char* str, int x, int y, SDL_Color c)
{
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, str, c);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    SDL_Rect r = { x - surface->w / 2, y - surface->h / 2, surface->w, surface->h };

    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &r);

    SDL_DestroyTexture(texture);
}

void Text_Draw_Center_With_Ratio(SDL_Renderer* renderer, TTF_Font* font, const char* str, int x, int y, SDL_Color c, double ratio_x, double ratio_y)
{
    SDL_Surface* surface = TTF_RenderUTF8_Blended(font, str, c);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    int w = surface->w * ratio_x;
    int h = surface->h * ratio_y;

    SDL_Rect r = { x - w / 2, y - h / 2, w, h };

    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &r);

    SDL_DestroyTexture(texture);
}
