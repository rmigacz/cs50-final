#include "game-board-functions.h"

#include "../core/game-parameters.h"

static Field init_chinchilla_fields(Board *board, Sprite *chinchilla);
static Field* draw_chinchilla_fields(const int map_width, const int map_height);

static Field* init_almonds_fields(Board *board, Sprite **almonds);
static Field* draw_almonds_fields(Board *board, const int almonds_count);

int init_chinchilla_position(Board *board, Sprite *chinchilla) {
	Field chinchilla_top_left_field = init_chinchilla_fields(board, chinchilla);
	if (chinchilla_top_left_field.value == -1) {
		printf("Failed to initialize chinchilla fields \n");
		return 1;
	}

	Position chinchilla_position = map_field_to_position(
			chinchilla_top_left_field);
	set_sprite_position(chinchilla, (int) chinchilla_position.x_pos,
			(int) chinchilla_position.y_pos);

	return 0;
}

int init_almonds_position(Board *board, Sprite **almonds) {
	Field *almonds_fields = init_almonds_fields(board, almonds);
	if (almonds_fields == NULL) {
		printf("Failed to initialize almonds fields \n");
		return 1;
	}

	Position almond_position = { 0, 0 };
	for (int i = 0; i < ALMONDS_COUNT; i++) {
		almond_position = map_field_to_position(almonds_fields[i]);
		set_sprite_position(almonds[i], (int) almond_position.x_pos,
				(int) almond_position.y_pos);
	}

	free(almonds_fields);
	return 0;
}

static Field init_chinchilla_fields(Board *board, Sprite *chinchilla) {
	Field *chinchilla_fields = draw_chinchilla_fields(BOARD_MAP_ROWS,
			BOARD_MAP_COLUMNS);
	if (chinchilla_fields == NULL) {
		printf("Failed to draw chinchilla fields \n");
		Field error_struct = { -1, -1, -1 };
		return error_struct;
	}

	set_board_fields(board, chinchilla_fields, CHINCHILLA_FIELDS_COUNT);

	Field chinchilla_top_left_field = chinchilla_fields[0];
	free(chinchilla_fields);

	return chinchilla_top_left_field;
}

static Field* draw_chinchilla_fields(const int map_width, const int map_height) {
	Field *fields = malloc(CHINCHILLA_FIELDS_COUNT * sizeof(Field));
	if (fields == NULL) {
		printf("Failed to allocate memory for chinchilla fields \n");
		return NULL;
	}

	Field top_left_field = draw_top_field(map_width, map_height,
			CHINCHILLA_ROW_FIELDS_COUNT, CHINCHILLA_COL_FIELDS_COUNT);

	int field_index = 0;
	for (int i = 0; i < CHINCHILLA_ROW_FIELDS_COUNT; i++) {
		for (int j = 0; j < CHINCHILLA_COL_FIELDS_COUNT; j++) {
			fields[field_index].row_number = top_left_field.row_number + i;
			fields[field_index].col_number = top_left_field.col_number + j;
			field_index++;
		}
	}

	return fields;
}


static Field* init_almonds_fields(Board *board, Sprite **almonds) {
	Field *almonds_fields = draw_almonds_fields(board, ALMONDS_COUNT);
	if (almonds_fields == NULL) {
		printf("Failed to draw almonds fields \n");
		return NULL;
	}

	return almonds_fields;
}

static Field* draw_almonds_fields(Board *board, const int almonds_count) {
	Field *fields = (Field*) malloc(almonds_count * sizeof(Field));
	if (fields == NULL) {
		printf("Failed to allocate memory for almonds fields \n");
		return NULL;
	}

	Field drawn_field;
	for (int i = 0; i < almonds_count; i++) {
		do {
			drawn_field = draw_top_field(BOARD_MAP_ROWS, BOARD_MAP_COLUMNS,
					ALMOND_ROW_FIELDS_COUNT, ALMOND_COL_FIELDS_COUNT);
		} while (is_board_field_set(board, drawn_field)
				|| is_field_neighbour_set(board, drawn_field));

		fields[i].row_number = drawn_field.row_number;
		fields[i].col_number = drawn_field.col_number;
		set_board_fields(board, &fields[i], 1);
	}

	return fields;
}

int reset_sprites_position(Board *board, Sprite *chinchilla, Sprite **almonds) {
	Position chinchilla_current_position = { get_sprite_x_position(chinchilla),
			get_sprite_y_position(chinchilla) };
	Field *chinchilla_fields = map_position_to_fields(
			chinchilla_current_position, CHINCHILLA_ROW_FIELDS_COUNT,
			CHINCHILLA_COL_FIELDS_COUNT);
	if (chinchilla_fields == NULL) {
		printf("Could not map chinchilla position to fields \n");
		return 1;
	}

	set_board_fields(board, chinchilla_fields, CHINCHILLA_FIELDS_COUNT);

	if (init_almonds_position(board, almonds) == 1) {
		printf("Error while initialization of almonds positions \n");
		return 1;
	}

	return 0;
}
