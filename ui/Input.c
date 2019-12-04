#include "Input.h"

#include "../graphics/graphics.h"

void process_key_events(Input *pressed_key) {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			pressed_key->close_requested = 1;
			break;
		case SDL_KEYDOWN:
			switch (event.key.keysym.scancode) {
			case SDL_SCANCODE_W:
			case SDL_SCANCODE_UP:
				pressed_key->up = 1;
				break;
			case SDL_SCANCODE_A:
			case SDL_SCANCODE_LEFT:
				pressed_key->left = 1;
				break;
			case SDL_SCANCODE_S:
			case SDL_SCANCODE_DOWN:
				pressed_key->down = 1;
				break;
			case SDL_SCANCODE_D:
			case SDL_SCANCODE_RIGHT:
				pressed_key->right = 1;
				break;
			}
			break;
		case SDL_KEYUP:
			switch (event.key.keysym.scancode) {
			case SDL_SCANCODE_W:
			case SDL_SCANCODE_UP:
				pressed_key->up = 0;
				break;
			case SDL_SCANCODE_A:
			case SDL_SCANCODE_LEFT:
				pressed_key->left = 0;
				break;
			case SDL_SCANCODE_S:
			case SDL_SCANCODE_DOWN:
				pressed_key->down = 0;
				break;
			case SDL_SCANCODE_D:
			case SDL_SCANCODE_RIGHT:
				pressed_key->right = 0;
				break;
			}
			break;
		}
	}
}
