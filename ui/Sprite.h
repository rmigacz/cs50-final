#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <stdlib.h>

typedef struct _Sprite {
	SDL_Texture *texture;
	SDL_Rect rectangle;
} Sprite;

Sprite* create_sprite(SDL_Renderer *renderer, const char *img_path, const int w,
		const int h);
 
void free_sprite(Sprite *sprite);

void free_sprites(Sprite **sprites, int length);

int get_sprite_x_position();

int get_sprite_y_position();

int get_sprite_width();

int get_sprite_height();

void set_sprite_position(Sprite *sprite, const int x_position,
		const int y_position);

#endif
