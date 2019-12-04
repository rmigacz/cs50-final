#include <math.h>

#include "Board.h"

#include "../core/game-parameters.h"

Board* create_board(const int map_rows, const int map_columns) {
	Board *map = malloc(sizeof(Board));
	if (map == NULL) {
		return NULL;
	}

	map->map_width = map_rows;
	map->map_height = map_columns;

	map->fields = (int**) calloc(map_rows, sizeof(int*));
	if (map->fields == NULL) {
		free_board(map);
		return NULL;
	}

	for (int row = 0; row < map_rows; row++) {
		map->fields[row] = (int*) calloc(map_columns, sizeof(int));
		if (map->fields[row] == NULL) {
			free_board(map);
			return NULL;
		}
	}

	return map;
}

void free_board(Board *map) {
	for (int row = 0; row < map->map_width; row++) {
		free(map->fields[row]), map->fields[row] = NULL;
	}
	free(map->fields), map->fields = NULL;
	free(map), map = NULL;
}

void set_board_fields(Board *map, Field *fields, const int fields_count) {
	for (int i = 0; i < fields_count; i++) {
		map->fields[fields[i].row_number][fields[i].col_number] = 1;
	}
}

int is_board_field_set(Board *board, Field field) {
	return board->fields[field.row_number][field.col_number] == 1;
}

int is_field_neighbour_set(Board *board, Field field) {
	int row_number = field.row_number;
	int col_number = field.col_number;

	Field up_field = { row_number + 1, col_number };
	if (up_field.row_number < BOARD_MAP_ROWS) {
		if (is_board_field_set(board, up_field)) {
			return 1;
		} else {
			is_field_neighbour_set(board, up_field);
		}
	}

	Field up_left_field = { row_number + 1, col_number - 1 };
	if (up_left_field.row_number < BOARD_MAP_ROWS
			&& up_left_field.col_number >= 0) {
		if (is_board_field_set(board, up_left_field)) {
			return 1;
		}
	}

	Field up_right_field = { row_number + 1, col_number + 1 };
	if (up_right_field.row_number < BOARD_MAP_ROWS
			&& up_right_field.col_number < BOARD_MAP_COLUMNS) {
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
			&& down_left_field.col_number < BOARD_MAP_COLUMNS) {
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
	if (right_field.col_number < BOARD_MAP_COLUMNS) {
		if (is_board_field_set(board, right_field)) {
			return 1;
		}
	}

	return 0;
}


Position map_field_to_position(Field field) {
	Position sprite_position = { field.col_number * FIELD_DIMENSION,
			field.row_number * FIELD_DIMENSION };
	return sprite_position;
}

Field* map_position_to_fields(Position position, int row_fields_count,
		int col_fields_count) {
	Field *fields = malloc(sizeof(Field) * row_fields_count * col_fields_count);
	if (fields == NULL) {
		printf("Could not allocate memory for array of fields \n");
		return NULL;
	}

	int field_index = 0;
	for (int i = 0; i < row_fields_count; i++) {
		for (int j = 0; j < col_fields_count; j++) {
			fields[field_index].row_number = floor(
					position.y_pos / FIELD_DIMENSION) + i;
			fields[field_index].col_number = floor(
					position.x_pos / FIELD_DIMENSION) + j;
			field_index++;
		}
	}

	return fields;
}

Field draw_top_field(const int map_width, const int map_height,
		const int row_fields_count, const int col_fields_count) {
	Field top_left_field;

	top_left_field.row_number = rand() % (map_width - row_fields_count);
	top_left_field.col_number = rand() % (map_height - col_fields_count);

	return top_left_field;
}

void clear_board(Board *board) {
	const int BOARD_WIDTH = board->map_width;
	const int BOARD_HEIGHT = board->map_height;

	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			board->fields[i][j] = 0;
		}
	}
}

void print_board(Board *board) {
	const int BOARD_WIDTH = board->map_width;
	const int BOARD_HEIGHT = board->map_height;

	for (int i = 0; i < BOARD_WIDTH; i++) {
		for (int j = 0; j < BOARD_HEIGHT; j++) {
			printf("%d ", board->fields[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");
}
