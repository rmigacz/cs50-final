#include "../include/Footer.h"

#include "../include/game-sdl-utils.h"

static ERRNO err = INIT_SUCCESS;

Footer* create_footer(int x, int y, int w, int h) {
	Footer* footer = malloc(sizeof(Footer));
	if (footer == NULL)  {
		return (err = FAILED_TO_INIT, NULL);
	}

	SDL_Rect area;
	area.x = x;
	area.y = y;
	area.w = w;
	area.h = h;
	footer->footer_area = area;

	SDL_Color message_color = { 0, 255, 0 };
	footer->message_color = message_color;

	footer->font = TTF_OpenFont("./resources/fonts/DroidSans.ttf", 32);
	if (footer->font == NULL) {
		printf("Error while loading font: %s \n", TTF_GetError());
		free_footer(footer);
		return (err = FAILED_TO_INIT, NULL);
	}

	return footer;
}

void set_footer_message(char* message, Footer* footer) {
	footer->message = message;
}

SDL_Texture* create_footer_texture(Footer* footer, SDL_Renderer* renderer) {
	SDL_Surface* surface = TTF_RenderText_Solid(footer->font, footer->message, footer->message_color);
	if (surface == NULL) {
		printf("Error while creating footer's surface: %s", TTF_GetError());
		return NULL;
	}

	SDL_Texture* texture = create_texture_from_surface(renderer, surface);
	SDL_FreeSurface(surface);
	return texture;
}

void free_footer(Footer* footer) {
	TTF_CloseFont(footer->font);
	footer->message = NULL;
	free(footer);
}

ERRNO get_footer_error() {
	return err;
}
