#include <SDL2/SDL_ttf.h>
#include <time.h>

#include "game-animation.h"
#include "game-parameters.h"

#include "../graphics/graphics.h"
#include "../board/Board.h"
#include "../ui/Window.h"
#include "../ui/Footer.h"
#include "../ui/Sprite.h"

static const char *WINDOW_TITLE = "Chinchilla The Almonds Eater";
static const char *CHILLA_IMG = "resources/pics/chinchilla.png";
static const char *ALMOND_IMG = "resources/pics/almond.png";

static int start_game();

int main(void) {
	srand(time(NULL));

	if (init_sdl() != 0) {
		return 1;
	}

	int game_result = start_game();

	cleanup_sdl();

	return game_result;
}

static int start_game() {
	Window *window = create_window(WINDOW_TITLE, WINDOW_DIMENSION,
			WINDOW_DIMENSION);
	if (window == NULL) {
		printf("Failed to create window");
		return 1;
	}

	Footer *footer = create_footer(WINDOW_FOOTER_X_POSITION,
			WINDOW_FOOTER_Y_POSITION, WINDOW_FOOTER_WIDTH,
			WINDOW_FOOTER_HEIGHT);

	if (footer == NULL) {
		printf("Failed to create footer");
		free_window(window);

		return 1;
	}

	Board *board = create_board(BOARD_MAP_ROWS, BOARD_MAP_COLUMNS);
	if (board == NULL) {
		printf("Failed to create board");
		free_window(window);
		free_footer(footer);

		return 1;
	}

	Sprite *chinchilla = create_sprite(window->renderer, CHILLA_IMG,
			CHINCHILLA_WIDTH, CHINCHILLA_HEIGHT);
	if (chinchilla == NULL) {
		printf("Failed to create sprite - chinchilla");
		free_window(window);
		free_footer(footer);
		free_board(board);

		return 1;
	}

	Sprite **almonds = malloc(ALMONDS_COUNT * sizeof(Sprite));
	if (almonds == NULL) {
		printf("Failed to allocate memory for array of almonds");
		free_window(window);
		free_footer(footer);
		free_board(board);
		free_sprite(chinchilla);

		return 1;
	}
	for (int i = 0; i < ALMONDS_COUNT; i++) {
		almonds[i] = create_sprite(window->renderer, ALMOND_IMG, ALMOND_WIDTH,
				ALMOND_HEIGHT);
		if (almonds[i] == NULL) {
			printf("Failed to create sprite - almond");
			free_window(window);
			free_footer(footer);
			free_board(board);
			free_sprite(chinchilla);
			free_sprites(almonds, ALMONDS_COUNT);

			return 1;
		}
	}

	int result = animate(window, footer, board, chinchilla, almonds);

	free_window(window);
	free_footer(footer);
	free_board(board);
	free_sprite(chinchilla);
	free_sprites(almonds, ALMONDS_COUNT);

	return result;
}
