#ifndef SDL_H
#define SDL_H

#include <SDL2/SDL.h>

int init_sdl();

void cleanup_sdl();

SDL_Window* create_sdl_window(const char *title, const int w, const int h);

SDL_Renderer* create_renderer(SDL_Window *window);

int set_renderer_color(SDL_Renderer*, int r, int g, int b);

SDL_Texture* create_texture_with_image(SDL_Renderer *renderer,
		const char *img_path);

SDL_Texture* create_texture_from_surface(SDL_Renderer *renderer,
		SDL_Surface *surface);

SDL_Rect create_texture_rectangle(SDL_Texture *texture, const int width,
		const int height);

void set_texture_position(SDL_Rect *dest, const int x, const int y);

void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination);

#endif
