#include "game-animation.h"
#include "game-parameters.h"

#include "game-board-functions.h"
#include "../board/Position.h"
#include "../graphics/graphics.h"
#include "../ui/Velocity.h"
#include "../ui/Input.h"

static Velocity determine_chinchilla_velocity(Input pressed_key);
static Position determine_chinchilla_position(Position position,
		Velocity velocity);
static Position detect_chinchilla_bounds_collision(Position position);

static int detect_chinchilla_collision_with_almonds(Position position,
		Sprite **almonds);

static int update_window_footer(Footer *footer, Window *window, char *message);

int animate(Window *window, Footer *footer, Board *board, Sprite *chinchilla,
		Sprite **almonds) {
	int result = 0;

	if (init_chinchilla_position(board, chinchilla) != 0) {
		printf("Error while initialization of chinchilla position \n");
		return 1;
	}

	if (init_almonds_position(board, almonds) != 0) {
		printf("Error while initialization of almonds position \n");
		return 1;
	}

	Velocity chinchilla_velocity = { 0, 0 };
	Position chinchilla_position = { get_sprite_x_position(chinchilla),
			get_sprite_y_position(chinchilla) };
	Input pressed_key = { 0, 0, 0, 0, 0 };

	Uint32 start_time = SDL_GetTicks();
	Uint32 current_time = 0;
	Uint32 eaten_almonds = 0;
	char footer_message[100];

	while (!pressed_key.close_requested && current_time < TIME_LIMIT) {
		process_key_events(&pressed_key);

		chinchilla_velocity = determine_chinchilla_velocity(pressed_key);
		chinchilla_position = determine_chinchilla_position(chinchilla_position,
				chinchilla_velocity);
		chinchilla_position = detect_chinchilla_bounds_collision(
				chinchilla_position);

		if (detect_chinchilla_collision_with_almonds(chinchilla_position,
				almonds) == 1) {
			eaten_almonds++;
			clear_board(board);
			result = reset_sprites_position(board, chinchilla, almonds);
			if (result == 1) {
				printf("Error while resetting sprites position \n");
				return 1;
			}
			SDL_Delay(1000 / 60);
		} else {
			set_sprite_position(chinchilla, (int) chinchilla_position.x_pos,
					(int) chinchilla_position.y_pos);
		}

		clear_window(window);
		add_sprite_to_window(chinchilla, window);
		add_sprites_to_window(almonds, window, ALMONDS_COUNT);

		current_time = (SDL_GetTicks() - start_time) / 1000;
		sprintf(footer_message, "Eaten almonds: %d Time: %d", eaten_almonds,
				current_time);
		result = update_window_footer(footer, window, footer_message);
		if (result == 1) {
			printf("Error while updating widnow's footer \n");
			return result;
		}

		update_window(window);
		SDL_Delay(1000 / 60);
	}

	return result;
}

static Velocity determine_chinchilla_velocity(Input pressed_key) {
	Velocity velocity = { 0, 0 };

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

static Position determine_chinchilla_position(Position position,
		Velocity velocity) {
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

static int detect_chinchilla_collision_with_almonds(Position position,
		Sprite **almonds) {
	int AMORTISATION = 49;
	int x_almond_position = 0;
	int y_almond_position = 0;

	for (int i = 0; i < ALMONDS_COUNT; i++) {
		x_almond_position = get_sprite_x_position(almonds[i]);
		y_almond_position = get_sprite_y_position(almonds[i]);

		// see: https://developer.mozilla.org/en-US/docs/Games/Techniques/2D_collision_detection
		if (position.x_pos < x_almond_position + ALMOND_WIDTH - AMORTISATION
				&& position.x_pos + CHINCHILLA_WIDTH
						> x_almond_position + AMORTISATION
				&& position.y_pos < y_almond_position + ALMOND_HEIGHT
				&& CHINCHILLA_HEIGHT + position.y_pos > y_almond_position) {
			return 1;
		}

	}

	return 0;
}

static int update_window_footer(Footer *footer, Window *window, char *message) {
	set_footer_message(message, footer);
	SDL_Texture *texture = create_footer_texture(footer, window->renderer);
	if (texture == NULL) {
		printf("Error while creating footer's texture: %s", SDL_GetError());
		return 1;
	}

	add_texture_to_window(texture, footer->footer_area, window);
	SDL_DestroyTexture(texture);

	return 0;
}
