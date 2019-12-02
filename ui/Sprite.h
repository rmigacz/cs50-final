#ifndef SPRITE_H
#define SPRITE_H

#include "../core/game-errno.h"

#include <SDL2/SDL.h>
#include <stdlib.h>

typedef struct _Sprite {
	SDL_Texture *texture;
	SDL_Rect rectangle;
} Sprite;

Sprite* create_sprite(SDL_Renderer *renderer, const char *img_path, const int w,
		const int h);
 
void free_sprite(Sprite *sprite);

int get_sprite_x_position();

int get_sprite_y_position();

int get_sprite_width();

int get_sprite_height();

void set_sprite_position(Sprite *sprite, const int x_position,
		const int y_position);

ERRNO get_sprite_error();

#endif
