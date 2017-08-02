#include "../include/game-animation.h"

#include "../include/Position.h"
#include "../include/Velocity.h"
#include "../include/game-parameters.h"
#include "../include/game-sdl-utils.h"
#include "../include/game-board-functions.h"

static void process_key_events(Input* input);

static Velocity determine_chinchilla_velocity(Input pressed_key);
static Position determine_chinchilla_position(Position position, Velocity velocity);
static Position detect_chinchilla_bounds_collision(Position position);

static int detect_chinchilla_collision_with_almonds(Position position, Sprite** almonds);

static void add_almonds_to_window(Sprite** almonds, Window* window);
static int update_window_footer(Footer* footer, Window* window, char* message);


int animate(Window* window, Footer* footer, Board* board,  Sprite* chinchilla, Sprite** almonds) {
	int result = 0;

	result =  init_sprites_position(board, chinchilla, almonds);
	if (result == 1) {
		printf("Error while initialization of sprites positions \n");
		return result;
	}

	Velocity chinchilla_velocity = {0, 0};
	Position chinchilla_position = {get_sprite_x_position(chinchilla), get_sprite_y_position(chinchilla)};
	Input pressed_key = {0, 0, 0, 0, 0};

    Uint32 start_time = SDL_GetTicks();
    Uint32 current_time = 0;
    Uint32 eaten_almonds = 0;
	char footer_message[100];

	while (!pressed_key.close_requested && current_time < TIME_LIMIT) {
		process_key_events(&pressed_key);

		chinchilla_velocity = determine_chinchilla_velocity(pressed_key);
		chinchilla_position = determine_chinchilla_position(chinchilla_position, chinchilla_velocity);
		chinchilla_position = detect_chinchilla_bounds_collision(chinchilla_position);

		if (detect_chinchilla_collision_with_almonds(chinchilla_position, almonds) == 1) {
			eaten_almonds++;
			clear_board(board);
			result = reset_sprites_position(board, chinchilla, almonds);
			if (result == 1) {
				printf("Error while resetting sprites position \n");
				return 1;
			}
			SDL_Delay(1000/60);
		} else {
			set_sprite_position(chinchilla, (int) chinchilla_position.x_pos, (int) chinchilla_position.y_pos);
		}

		clear_window(window);
		add_sprite_to_window(chinchilla, window);
		add_almonds_to_window(almonds, window);

		current_time = (SDL_GetTicks() - start_time) / 1000;
		sprintf(footer_message, "Eaten almonds: %d Time: %d", eaten_almonds, current_time);
		result = update_window_footer(footer, window, footer_message);
		if (result == 1) {
			printf("Error while updating widnow's footer \n");
			return result;
		}

		update_window(window);
		SDL_Delay(1000/60);
	}

	return result;
}

static void process_key_events(Input* pressed_key) {
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

static Velocity determine_chinchilla_velocity(Input pressed_key) {
	Velocity velocity = {0, 0};

	if (pressed_key.up && !pressed_key.down) {
		velocity.y_vel = -SPEED;
	}

	if (pressed_key.down && !pressed_key.up) {
		velocity.y_vel = SPEED;
	}

	if (pressed_key.left && !pressed_key.right) {
		velocity.x_vel = -SPEED;
	}

	if (pressed_key.right && !pressed_key.left) {
		velocity.x_vel = SPEED;
	}

	return velocity;
}

static Position determine_chinchilla_position(Position position, Velocity velocity) {
	position.x_pos += velocity.x_vel / 60;
	position.y_pos += velocity.y_vel / 60;
	return position;
}

static Position detect_chinchilla_bounds_collision(Position position) {
	if (position.x_pos < 0) {
		position.x_pos = 0;
	}

	if (position.y_pos < 0) {
		position.y_pos = 0;
	}

	if (position.x_pos > WINDOW_BOARD_WIDTH - CHINCHILLA_WIDTH) {
		position.x_pos = WINDOW_BOARD_WIDTH - CHINCHILLA_WIDTH - 1;
	}

	if (position.y_pos > WINDOW_BOARD_HEIGHT - CHINCHILLA_HEIGHT) {
		position.y_pos = WINDOW_BOARD_HEIGHT - CHINCHILLA_HEIGHT - 1;
	}

	return position;
}

static int detect_chinchilla_collision_with_almonds(Position position, Sprite** almonds) {
	int AMORTISATION = 49;
	int x_almond_position = 0;
	int y_almond_position = 0;

	for (int i = 0; i < ALMONDS_COUNT; i++) {
		x_almond_position = get_sprite_x_position(almonds[i]);
		y_almond_position = get_sprite_y_position(almonds[i]);

		// see: https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection
		if (position.x_pos < x_almond_position + ALMOND_WIDTH - AMORTISATION &&
			position.x_pos  + CHINCHILLA_WIDTH > x_almond_position + AMORTISATION &&
			position.y_pos < y_almond_position + ALMOND_HEIGHT &&
			CHINCHILLA_HEIGHT + position.y_pos > y_almond_position) {
			return 1;
		}

	}

	return 0;
}

static void add_almonds_to_window(Sprite** almonds, Window* window) {
	for (int i = 0; i < ALMONDS_COUNT; i++) {
		add_sprite_to_window(almonds[i], window);
	}
}

static int update_window_footer(Footer* footer, Window* window, char* message) {
	set_footer_message(message, footer);
	SDL_Texture* texture = 	create_footer_texture(footer, window->renderer);
	if (texture == NULL) {
		printf("Error while creating footer's texture: %s", SDL_GetError());
		return 1;
	}

	add_texture_to_window(texture, footer->footer_area, window);
	SDL_DestroyTexture(texture);

	return 0;
}
