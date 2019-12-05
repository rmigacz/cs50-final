#include <math.h>

#include "Board.h"

Board* create_board(const int rows_count, const int columns_count) {
	Board *board = malloc(sizeof(Board));
	if (board == NULL) {
		return NULL;
	}

	board->rows_count = rows_count;
	board->columns_count = columns_count;

	board->fields = (int**) calloc(rows_count, sizeof(int*));
	if (board->fields == NULL) {
		free_board(board);
		return NULL;
	}

	for (int row = 0; row < rows_count; row++) {
		board->fields[row] = (int*) calloc(columns_count, sizeof(int));
		if (board->fields[row] == NULL) {
			free_board(board);
			return NULL;
		}
	}

	return board;
}

void free_board(Board *board) {
	for (int row = 0; row < board->rows_count; row++) {
		free(board->fields[row]), board->fields[row] = NULL;
	}
	free(board->fields), board->fields = NULL;
	free(board), board = NULL;
}

void set_board_fields(Board *board, Field *fields, const int fields_count) {
	for (int i = 0; i < fields_count; i++) {
		board->fields[fields[i].row_number][fields[i].col_number] = 1;
	}
}

int is_board_field_set(Board *board, Field field) {
	return board->fields[field.row_number][field.col_number] == 1;
}

int is_field_neighbour_set(Board *board, Field field) {
	const int rows_count = board->rows_count;
	const int columns_count = board->columns_count;

	const int row_number = field.row_number;
	const int col_number = field.col_number;

	Field up_field = { row_number + 1, col_number };
	if (up_field.row_number < rows_count) {
		if (is_board_field_set(board, up_field)) {
			return 1;
		} else {
			is_field_neighbour_set(board, up_field);
		}
	}

	Field up_left_field = { row_number + 1, col_number - 1 };
	if (up_left_field.row_number < rows_count
			&& up_left_field.col_number >= 0) {
		if (is_board_field_set(board, up_left_field)) {
			return 1;
		}
	}

	Field up_right_field = { row_number + 1, col_number + 1 };
	if (up_right_field.row_number < rows_count
			&& up_right_field.col_number < columns_count) {
		if (is_board_field_set(board, up_right_field)) {
			return 1;
		}
	}

	Field down_field = { row_number - 1, col_number };
	if (down_field.row_number >= 0) {
		if (is_board_field_set(board, down_field)) {
			return 1;
		}
	}

	Field down_left_field = { row_number - 1, col_number - 1 };
	if (down_left_field.row_number >= 0 && down_left_field.col_number >= 0) {
		if (is_board_field_set(board, down_left_field)) {
			return 1;
		}
	}

	Field down_right_field = { row_number - 1, col_number + 1 };
	if (down_right_field.row_number >= 0
			&& down_left_field.col_number < columns_count) {
		if (is_board_field_set(board, down_right_field)) {
			return 1;
		}
	}

	Field left_field = { row_number, col_number - 1 };
	if (left_field.col_number >= 0) {
		if (is_board_field_set(board, left_field)) {
			return 1;
		}
	}

	Field right_field = { row_number, col_number + 1 };
	if (right_field.col_number < columns_count) {
		if (is_board_field_set(board, right_field)) {
			return 1;
		}
	}

	return 0;
}


Position map_field_to_position(Field field, const int field_dimension) {
	Position sprite_position = { field.col_number * field_dimension,
			field.row_number * field_dimension };
	return sprite_position;
}

Field* map_position_to_fields(Position position, const int row_fields_count,
		const int col_fields_count, const int field_dimension) {
	Field *fields = malloc(sizeof(Field) * row_fields_count * col_fields_count);
	if (fields == NULL) {
		printf("Could not allocate memory for array of fields \n");
		return NULL;
	}

	int field_index = 0;
	for (int i = 0; i < row_fields_count; i++) {
		for (int j = 0; j < col_fields_count; j++) {
			fields[field_index].row_number = floor(
					position.y_pos / field_dimension) + i;
			fields[field_index].col_number = floor(
					position.x_pos / field_dimension) + j;
			field_index++;
		}
	}

	return fields;
}

Field draw_top_left_field(Board *board, const int row_fields_count,
		const int col_fields_count) {
	Field top_left_field;

	top_left_field.row_number = rand() % (board->rows_count - row_fields_count);
	top_left_field.col_number = rand()
			% (board->columns_count - col_fields_count);

	return top_left_field;
}

void clear_board(Board *board) {
	const int rows_count = board->rows_count;
	const int columns_count = board->columns_count;

	for (int i = 0; i < rows_count; i++) {
		for (int j = 0; j < columns_count; j++) {
			board->fields[i][j] = 0;
		}
	}
}

void print_board(Board *board) {
	const int rows_count = board->rows_count;
	const int columns_count = board->columns_count;

	for (int i = 0; i < rows_count; i++) {
		for (int j = 0; j < columns_count; j++) {
			printf("%d ", board->fields[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}
