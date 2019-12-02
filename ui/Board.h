#ifndef BOARDFUNC_H
#define BOARDFUNC_H

#include "../include/game-errno.h"

#include <SDL2/SDL.h>
#include <stdlib.h>

typedef struct _Board {
	int **fields;
	int map_width;
	int map_height;
} Board;

typedef struct _Field {
	int row_number;
	int col_number;
	int value;
} Field;

Board* create_board(const int map_width, const int map_height);

void free_board(Board *board);

void set_board_fields(Board *board, Field *fields, const int fields_count);

int is_board_field_set(Board *board, Field field);

void clear_board(Board *board);

void print_board(Board *board);

ERRNO get_board_error();

#endif

