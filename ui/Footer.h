#ifndef FOOTER_H
#define FOOTER_H

#include "../core/game-errno.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>

typedef struct _Footer {
	SDL_Rect footer_area;
	SDL_Color message_color;
	TTF_Font *font;
	char *message;
} Footer;

Footer* create_footer(int x, int y, int w, int h);

void free_footer(Footer *footer);

void set_footer_message(char *message, Footer *footer);

SDL_Texture* create_footer_texture(Footer *footer, SDL_Renderer *renderer);

ERRNO get_footer_error();

#endif
