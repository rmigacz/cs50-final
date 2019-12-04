#ifndef WINDOW_H
#define WINDOW_H

#include <stdlib.h>
#include <SDL2/SDL.h>

#include "Sprite.h"

typedef struct _Window {
	SDL_Window *window;
	SDL_Renderer *renderer;
} Window;

Window* create_window(const char *title, const int width, const int height);

void free_window(Window *window);

void clear_window(Window *window);

void add_sprite_to_window(Sprite *sprite, Window *window);

void add_texture_to_window(SDL_Texture *texture, SDL_Rect rectangle,
		Window *window);

void update_window(Window *window);

#endif
