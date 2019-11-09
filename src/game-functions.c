#include "../include/game-functions.h"

#include "../include/Board.h"
#include "../include/Window.h"
#include "../include/Footer.h"
#include "../include/Board.h"
#include "../include/Sprite.h"
#include "../include/game-parameters.h"
#include "../include/game-animation.h"

#include <SDL2/SDL_ttf.h>
#include <time.h>

static const char *WINDOW_TITLE = "Chinchilla The Almonds Eater";
static const char *CHILLA_IMG = "resources/pics/chinchilla.png";
static const char *ALMOND_IMG = "resources/pics/almond.png";

static void cleanup(Window *window, Footer *footer, Board *board,
		Sprite *chinchilla, Sprite **almonds);

int start_game() {
	srand(time(NULL));

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
		printf("Error initializing SDL: %s\n", SDL_GetError());
		return 1;
	}

	if (TTF_Init() != 0) {
		printf("Error while initialization SDL_TTF: %s\n", TTF_GetError());
		return 1;
	}

	Window *window = create_window(WINDOW_TITLE, WINDOW_DIMENSION,
			WINDOW_DIMENSION);
	if (window == NULL) {
		printf("%d", get_window_error());
		return 1;
	}

	Footer *footer = create_footer(WINDOW_FOOTER_X_POSITION,
			WINDOW_FOOTER_Y_POSITION, WINDOW_FOOTER_WIDTH,
			WINDOW_FOOTER_HEIGHT);
	;
	if (footer == NULL) {
		printf("%d", get_footer_error());
		cleanup(window, NULL, NULL, NULL, NULL);
		return 1;
	}

	Board *board = create_board(BOARD_MAP_ROWS, BOARD_MAP_COLUMNS);
	if (board == NULL) {
		printf("%d", get_board_error());
		cleanup(window, footer, NULL, NULL, NULL);
		return 1;
	}

	Sprite *chinchilla = create_sprite(window->renderer, CHILLA_IMG,
			CHINCHILLA_WIDTH, CHINCHILLA_HEIGHT);
	if (chinchilla == NULL) {
		printf("%d", get_sprite_error());
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
			printf("%d", get_sprite_error());
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

	TTF_Quit();
	SDL_Quit();
}
