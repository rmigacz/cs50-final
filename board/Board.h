#ifndef BOARDFUNC_H
#define BOARDFUNC_H

#include "Position.h"

typedef struct _Board {
	int **fields;
	int rows_count;
	int columns_count;
} Board;

typedef struct _Field {
	int row_number;
	int col_number;
	int value;
} Field;

Board* create_board(const int rows_count, const int columns_count);

void free_board(Board *board);

void set_board_fields(Board *board, Field *fields, const int fields_count);

int is_board_field_set(Board *board, Field field);

int is_field_neighbour_set(Board *board, Field field);

Position map_field_to_position(Field field, const int field_dimension);

Field* map_position_to_fields(Position position, const int row_fields_count,
		const int col_fields_count, const int field_dimension);

Field draw_top_left_field(Board *board, const int row_fields_count,
		const int col_fields_count);

void clear_board(Board *board);

void print_board(Board *board);

#endif

