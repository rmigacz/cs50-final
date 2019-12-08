#include "Window.h"

#include "../graphics/graphics.h"

Window* create_window(const char *title, const int width, const int height) {
	Window *window = malloc(sizeof(Window));
	if (window == NULL) {
		return NULL;
	}

	window->window = create_sdl_window(title, width, height);
	if (window->window == NULL) {
		printf("error creating window: %s\n", SDL_GetError());
		free_window(window);
		return NULL;
	}

	window->renderer = create_renderer(window->window);
	if (window->renderer == NULL) {
		printf("error creating renderer: %s\n", SDL_GetError());
		free_window(window);
		return NULL;
	}

	if (set_renderer_color(window->renderer, 255, 255, 255) != 0) {
		printf("error setting renderer color: %s\n", SDL_GetError());
		free_window(window);
		return NULL;
	}

	return window;
}

void free_window(Window *window) {
	SDL_DestroyWindow(window->window), window->window = NULL;
	SDL_DestroyRenderer(window->renderer), window->renderer = NULL;
	free(window), window = NULL;
}

void clear_window(Window *window) {
	SDL_RenderClear(window->renderer);
}

void add_sprite_to_window(Sprite *sprite, Window *window) {
	SDL_RenderCopy(window->renderer, sprite->texture, NULL,
			&(sprite->rectangle));
}

void add_sprites_to_window(Sprite **sprites, Window *window,
		const int sprites_count) {
	for (int i = 0; i < sprites_count; i++) {
		add_sprite_to_window(sprites[i], window);
	}
}

void add_surface_to_window(SDL_Surface *surface, int x, int y, Window *window) {
	SDL_Surface *window_surface = SDL_GetWindowSurface(window->window);
	apply_surface(x, y, surface, window_surface);
}

void add_texture_to_window(SDL_Texture *texture, SDL_Rect rectangle,
		Window *window) {
	SDL_RenderCopy(window->renderer, texture, NULL, &(rectangle));
}

void update_window(Window *window) {
	SDL_RenderPresent(window->renderer);
}
