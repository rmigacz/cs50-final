#ifndef GAMEBOARDFUNCTIONS_H
#define GAMEBOARDFUNCTIONS_H

#include "Board.h"
#include "Position.h"

#include "../ui/Sprite.h"

int init_sprites_position(Board *board, Sprite *chinchilla, Sprite **almonds);
int reset_sprites_position(Board *board, Sprite *chinchilla, Sprite **almonds);

#endif
