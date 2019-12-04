#ifndef GAMEBOARDFUNCTIONS_H
#define GAMEBOARDFUNCTIONS_H

#include "Board.h"
#include "Position.h"

#include "../ui/Sprite.h"

int init_chinchilla_position(Board *board, Sprite *chinchilla);

int init_almonds_position(Board *board, Sprite **almonds);

int reset_sprites_position(Board *board, Sprite *chinchilla, Sprite **almonds);

#endif
