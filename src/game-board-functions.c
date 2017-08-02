#include "../include/game-board-functions.h"

#include "../include/game-parameters.h"

static int init_chinchilla_position(Board* board, Sprite* chinchilla);
static Field init_chinchilla_fields(Board* board, Sprite* chinchilla);
static Field* draw_chinchilla_fields(const int map_width, const int map_height);

static int init_almonds_position(Board* board, Sprite** almonds);
static Field* init_almonds_fields(Board* board, Sprite** almonds);
static Field* draw_almonds_fields(Board* board, const int almonds_count);
static int is_field_neighbour_set(Board* board, Field field);

static Field* map_sprite_position_to_fields(Position position, int row_fields_count, int col_fields_count);
static Position map_sprite_field_to_position(Field field);
static Field draw_sprite_top_field(const int map_width, const int map_height, const int row_fields_count, const int col_fields_count);

int init_sprites_position(Board* board, Sprite* chinchilla, Sprite** almonds) {
	int result = 0;

	result = init_chinchilla_position(board, chinchilla);
	if (result == 1) {
		printf("Error while initialization of chinchilla position \n");
		return result;
	}
	result = init_almonds_position(board, almonds);
	if (result == 1) {
		printf("Error while initialization of almonds positions \n");
		return result;
	}

	return result;
}

static int init_chinchilla_position(Board* board, Sprite* chinchilla) {
	Field chinchilla_top_left_field = init_chinchilla_fields(board, chinchilla);
	if (chinchilla_top_left_field.value == -1 ) {
		printf("Failed to initialize chinchilla fields \n");
		return 1;
	}

	Position chinchilla_position = map_sprite_field_to_position(chinchilla_top_left_field);
	set_sprite_position(chinchilla, (int) chinchilla_position.x_pos, (int) chinchilla_position.y_pos);

	return 0;
}

static Field init_chinchilla_fields(Board* board, Sprite* chinchilla) {
	Field* chinchilla_fields = draw_chinchilla_fields(BOARD_MAP_ROWS, BOARD_MAP_COLUMNS);
	if (chinchilla_fields == NULL) {
		printf("Failed to draw chinchilla fields \n");
		Field error_struct = {-1, -1, -1};
		return error_struct;
	}

	set_board_fields(board, chinchilla_fields, CHINCHILLA_FIELDS_COUNT);

	Field chinchilla_top_left_field = chinchilla_fields[0];
	free(chinchilla_fields);

	return chinchilla_top_left_field;
}

static Field* draw_chinchilla_fields(const int map_width, const int map_height) {
	Field* fields = malloc(CHINCHILLA_FIELDS_COUNT * sizeof(Field));
	if (fields == NULL) {
		printf("Failed to allocate memory for chinchilla fields \n");
		return NULL;
	}

	Field top_left_field = draw_sprite_top_field(map_width, map_height, CHINCHILLA_ROW_FIELDS_COUNT, CHINCHILLA_COL_FIELDS_COUNT);

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

static int init_almonds_position(Board* board, Sprite** almonds) {
	Field* almonds_fields = init_almonds_fields(board, almonds);
	if (almonds_fields == NULL) {
		printf("Failed to initialize almonds fields \n");
		return 1;
	}

	Position almond_position = {0, 0};
	for (int i = 0; i < ALMONDS_COUNT; i++) {
		almond_position = map_sprite_field_to_position(almonds_fields[i]);
		set_sprite_position(almonds[i], (int) almond_position.x_pos, (int) almond_position.y_pos);
	}

	free(almonds_fields);
	return 0;
}

static Field* init_almonds_fields(Board* board, Sprite** almonds) {
	Field* almonds_fields = draw_almonds_fields(board, ALMONDS_COUNT);
	if (almonds_fields == NULL) {
		printf("Failed to draw almonds fields \n");
		return NULL;
	}

	return almonds_fields;
}

static Field* draw_almonds_fields(Board* board, const int almonds_count) {
	Field* fields = (Field*) malloc(almonds_count * sizeof(Field));
	if (fields == NULL) {
		printf("Failed to allocate memory for almonds fields \n");
		return NULL;
	}

	Field drawn_field;
	for (int i = 0; i < almonds_count; i++) {
		do {
			drawn_field = draw_sprite_top_field(BOARD_MAP_ROWS, BOARD_MAP_COLUMNS, ALMOND_ROW_FIELDS_COUNT, ALMOND_COL_FIELDS_COUNT);
		} while (is_board_field_set(board, drawn_field) || is_field_neighbour_set(board, drawn_field));

		fields[i].row_number = drawn_field.row_number;
		fields[i].col_number = drawn_field.col_number;
		set_board_fields(board, &fields[i], 1);
	}

	return fields;
}

static int is_field_neighbour_set(Board* board, Field field) {
	int row_number = field.row_number;
	int col_number = field.col_number;

	Field up_field = {row_number + 1, col_number};
	if (up_field.row_number < BOARD_MAP_ROWS) {
		if (is_board_field_set(board, up_field)) {
			return 1;
		} else {
			is_field_neighbour_set(board, up_field);
		}
	}

	Field up_left_field = {row_number + 1, col_number - 1};
	if (up_left_field.row_number < BOARD_MAP_ROWS && up_left_field.col_number >= 0) {
		if (is_board_field_set(board, up_left_field)) {
			return 1;
		}
	}

	Field up_right_field = {row_number + 1, col_number + 1};
	if (up_right_field.row_number < BOARD_MAP_ROWS && up_right_field.col_number < BOARD_MAP_COLUMNS) {
		if (is_board_field_set(board, up_right_field)) {
			return 1;
		}
	}

	Field down_field = {row_number - 1, col_number};
	if (down_field.row_number >= 0) {
		if (is_board_field_set(board, down_field)) {
			return 1;
		}
	}

	Field down_left_field = {row_number - 1, col_number - 1};
	if (down_left_field.row_number >= 0 && down_left_field.col_number >= 0) {
		if (is_board_field_set(board, down_left_field)) {
			return 1;
		}
	}

	Field down_right_field = {row_number - 1, col_number + 1};
	if (down_right_field.row_number >= 0 && down_left_field.col_number < BOARD_MAP_COLUMNS) {
		if (is_board_field_set(board, down_right_field)) {
			return 1;
		}
	}

	Field left_field = {row_number, col_number - 1};
	if (left_field.col_number >= 0) {
		if (is_board_field_set(board, left_field)) {
			return 1;
		}
	}

	Field right_field = {row_number, col_number + 1};
	if (right_field.col_number < BOARD_MAP_COLUMNS) {
		if (is_board_field_set(board, right_field)) {
			return 1;
		}
	}

	return 0;
}

int reset_sprites_position(Board* board, Sprite* chinchilla, Sprite** almonds) {
	Position chinchilla_current_position = {get_sprite_x_position(chinchilla), get_sprite_y_position(chinchilla)};
	Field* chinchilla_fields = map_sprite_position_to_fields(chinchilla_current_position, CHINCHILLA_ROW_FIELDS_COUNT, CHINCHILLA_COL_FIELDS_COUNT);
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

static Field* map_sprite_position_to_fields(Position position, int row_fields_count, int col_fields_count) {
	Field* fields = malloc(sizeof(Field) * row_fields_count * col_fields_count);
	if (fields == NULL) {
		printf("Could not allocate memory for array of fields \n");
		return NULL;
	}

	int field_index = 0;
	for (int i = 0; i < row_fields_count; i++) {
		for (int j = 0; j < col_fields_count; j++) {
			fields[field_index].row_number = floor(position.y_pos / FIELD_DIMENSION) + i;
			fields[field_index].col_number = floor(position.x_pos / FIELD_DIMENSION) + j;
			field_index++;
		}
	}

	return fields;
}

static Position map_sprite_field_to_position(Field field) {
	Position sprite_position = { field.col_number * FIELD_DIMENSION, field.row_number * FIELD_DIMENSION };
	return sprite_position;
}

static Field draw_sprite_top_field(const int map_width, const int map_height, const int row_fields_count, const int col_fields_count) {
	Field top_left_field;

	top_left_field.row_number = rand() % (map_width - row_fields_count);
	top_left_field.col_number = rand() % (map_height - col_fields_count);

	return top_left_field;
}
