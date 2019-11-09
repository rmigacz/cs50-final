#ifndef GAMEBOARDFUNCTIONS_H
#define GAMEBOARDFUNCTIONS_H

#include "../include/Board.h"
#include "../include/Sprite.h"
#include "../include/Position.h"

int init_sprites_position(Board *board, Sprite *chinchilla, Sprite **almonds);
int reset_sprites_position(Board *board, Sprite *chinchilla, Sprite **almonds);

#endif
