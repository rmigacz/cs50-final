#include "Sprite.h"

#include "../graphics/graphics.h"

Sprite* create_sprite(SDL_Renderer *renderer, const char *img_path, const int w,
		const int h) {
	Sprite *sprite = malloc(sizeof(Sprite));
	if (sprite == NULL) {
		return NULL;
	}

	sprite->texture = create_texture_with_image(renderer, img_path);
	if (sprite->texture == NULL) {
		free_sprite(sprite);
		return NULL;
	}

	sprite->rectangle = create_texture_rectangle(sprite->texture, w, h);

	return sprite;
}

void free_sprite(Sprite *sprite) {
	SDL_DestroyTexture(sprite->texture), sprite->texture = NULL;
	free(sprite), sprite = NULL;
}

void free_sprites(Sprite **sprites, int length) {
	for (int i = 0; i < length; i++) {
		if (sprites[i] != NULL) {
			free_sprite(sprites[i]);
		}
	}
	free(sprites);
}

int get_sprite_x_position(Sprite *sprite) {
	return sprite->rectangle.x;
}

int get_sprite_y_position(Sprite *sprite) {
	return sprite->rectangle.y;
}

int get_sprite_width(Sprite *sprite) {
	return sprite->rectangle.w;
}

int get_sprite_height(Sprite *sprite) {
	return sprite->rectangle.h;
}

void set_sprite_position(Sprite *sprite, const int x_position,
		const int y_position) {
	sprite->rectangle.x = x_position;
	sprite->rectangle.y = y_position;
}
