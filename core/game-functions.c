#include "game-functions.h"

#include "game-parameters.h"
#include "game-animation.h"

#include "../graphics/graphics.h"
#include "../ui/Board.h"
#include "../ui/Window.h"
#include "../ui/Footer.h"
#include "../ui/Board.h"
#include "../ui/Sprite.h"


#include <SDL2/SDL_ttf.h>
#include <time.h>

static const char *WINDOW_TITLE = "Chinchilla The Almonds Eater";
static const char *CHILLA_IMG = "resources/pics/chinchilla.png";
static const char *ALMOND_IMG = "resources/pics/almond.png";

static void cleanup(Window *window, Footer *footer, Board *board,
		Sprite *chinchilla, Sprite **almonds);

int start_game() {
	srand(time(NULL));

	if (init_sdl() != 0) {
		return 1;
	}

	Window *window = create_window(WINDOW_TITLE, WINDOW_DIMENSION,
			WINDOW_DIMENSION);
	if (window == NULL) {
		printf("Failed to create window");
		return 1;
	}

	Footer *footer = create_footer(WINDOW_FOOTER_X_POSITION,
			WINDOW_FOOTER_Y_POSITION, WINDOW_FOOTER_WIDTH,
			WINDOW_FOOTER_HEIGHT);
	;
	if (footer == NULL) {
		printf("Failed to create footer");
		cleanup(window, NULL, NULL, NULL, NULL);
		return 1;
	}

	Board *board = create_board(BOARD_MAP_ROWS, BOARD_MAP_COLUMNS);
	if (board == NULL) {
		printf("Failed to create board");
		cleanup(window, footer, NULL, NULL, NULL);
		return 1;
	}

	Sprite *chinchilla = create_sprite(window->renderer, CHILLA_IMG,
			CHINCHILLA_WIDTH, CHINCHILLA_HEIGHT);
	if (chinchilla == NULL) {
		printf("Failed to create sprite - chinchilla");
		cleanup(window, footer, board, NULL, NULL);
		return 1;
	}

	Sprite **almonds = malloc(ALMONDS_COUNT * sizeof(Sprite));
	if (almonds == NULL) {
		printf("Failed to allocate memory for array of almonds");
		cleanup(window, footer, board, chinchilla, NULL);
		return 1;
	}
	for (int i = 0; i < ALMONDS_COUNT; i++) {
		almonds[i] = create_sprite(window->renderer, ALMOND_IMG, ALMOND_WIDTH,
				ALMOND_HEIGHT);
		if (almonds[i] == NULL) {
			printf("Failed to create sprite - almond");
			cleanup(window, footer, board, chinchilla, almonds);
			return 1;
		}
	}

	int result = animate(window, footer, board, chinchilla, almonds);

	cleanup(window, footer, board, chinchilla, almonds);

	return result;
}

static void cleanup(Window *window, Footer *footer, Board *board,
		Sprite *chinchilla, Sprite **almonds) {
	if (window != NULL) {
		free_window(window);
	}

	if (footer != NULL) {
		free_footer(footer);
	}

	if (board != NULL) {
		free_board(board);
	}

	if (chinchilla != NULL) {
		free_sprite(chinchilla);
	}

	if (almonds != NULL) {
		for (int i = 0; i < ALMONDS_COUNT; i++) {
			free_sprite(almonds[i]);
		}
		free(almonds);
	}

	cleanup_sdl();
}
