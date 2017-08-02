#include "../include/Sprite.h"

#include "../include/game-sdl-utils.h"

static ERRNO err = INIT_SUCCESS;

Sprite* create_sprite(SDL_Renderer* renderer, const char* img_path, const int sprite_width, const int sprite_height) {
    Sprite* sprite = malloc(sizeof(Sprite));
    if (sprite == NULL)  {
        return (err = FAILED_TO_INIT, NULL);
    }

    sprite->texture = create_texture_with_image(renderer, img_path);
    if (sprite->texture == NULL) {
    	free_sprite(sprite);
    	return (err = FAILED_TO_INIT, NULL);
    }

    sprite->rectangle = create_texture_rectangle(sprite->texture, sprite_width, sprite_height);

    return (err = INIT_SUCCESS, sprite);
}

void free_sprite(Sprite* sprite) {
	SDL_DestroyTexture(sprite->texture), sprite->texture = NULL;
	free(sprite), sprite = NULL;
}

int get_sprite_x_position(Sprite* sprite) {
	return sprite->rectangle.x;
}

int get_sprite_y_position(Sprite* sprite) {
	return sprite->rectangle.y;
}

int get_sprite_width(Sprite* sprite) {
	return sprite->rectangle.w;
}

int get_sprite_height(Sprite* sprite) {
	return sprite->rectangle.h;
}

void set_sprite_position(Sprite* sprite, const int x_position, const int y_position) {
	sprite->rectangle.x = x_position;
	sprite->rectangle.y = y_position;
}

ERRNO get_sprite_error() {
     return err;
}
