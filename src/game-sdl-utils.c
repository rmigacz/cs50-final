#include "../include/game-sdl-utils.h"

#include <SDL2/SDL_image.h>
#include <stdlib.h>

SDL_Window* create_sdl_window(const char *title, const int width,
		const int height) {
	return SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, width, height, 0);
}

SDL_Renderer* create_renderer(SDL_Window *window) {
	return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

SDL_Texture* create_texture_with_image(SDL_Renderer *renderer,
		const char *img_path) {
	SDL_Texture *texture = NULL;
	SDL_Surface *loaded_image = IMG_Load(img_path);

	if (!loaded_image) {
		printf("Error while creating texture with image: %s\n", IMG_GetError());
		return NULL;
	}

	texture = create_texture_from_surface(renderer, loaded_image);

	SDL_FreeSurface(loaded_image);

	return texture;
}

SDL_Texture* create_texture_from_surface(SDL_Renderer *renderer,
		SDL_Surface *surface) {
	return SDL_CreateTextureFromSurface(renderer, surface);
}

SDL_Rect create_texture_rectangle(SDL_Texture *texture, const int width,
		const int height) {
	SDL_Rect dest;
	dest.x = 0;
	dest.y = 0;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	dest.w = width;
	dest.h = height;

	return dest;
}

void set_texture_position(SDL_Rect *dest, const int x, const int y) {
	dest->x = x;
	dest->y = y;
}

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination) {
	SDL_Rect offset;

	offset.x = x;
	offset.y = y;

	SDL_BlitSurface(source, NULL, destination, &offset);
}

