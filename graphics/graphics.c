#include <stdlib.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "graphics.h"

int init_sdl() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
		printf("Error initializing SDL: %s\n", SDL_GetError());
		return 1;
	}

	if (TTF_Init() != 0) {
		printf("Error while initialization SDL_TTF: %s\n", TTF_GetError());
		return 1;
	}

	return 0;
}

void cleanup_sdl() {
	TTF_Quit();
	SDL_Quit();
}

SDL_Window* create_sdl_window(const char *title, const int w, const int h) {
	return SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, w, h, 0);
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

SDL_Rect create_texture_rectangle(SDL_Texture *texture, const int w,
		const int h) {
	SDL_Rect dest;
	dest.x = 0;
	dest.y = 0;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
	dest.w = w;
	dest.h = h;

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

