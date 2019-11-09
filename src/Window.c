#include "../include/Window.h"

#include "../include/game-sdl-utils.h"

static ERRNO err = INIT_SUCCESS;

Window* create_window(const char *title, const int width, const int height) {
	Window *window = malloc(sizeof(Window));
	if (window == NULL) {
		return (err = FAILED_TO_INIT, NULL);
	}

	window->window = create_sdl_window(title, width, height);
	if (window->window == NULL) {
		printf("error creating window: %s\n", SDL_GetError());
		free_window(window);
		return (err = FAILED_TO_INIT, NULL);
	}

	window->renderer = create_renderer(window->window);
	if (window->renderer == NULL) {
		printf("error creating renderer: %s\n", SDL_GetError());
		free_window(window);
		return (err = FAILED_TO_INIT, NULL);
	}

	return (err = INIT_SUCCESS, window);
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

ERRNO get_window_error() {
	return err;
}
