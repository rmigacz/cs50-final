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
