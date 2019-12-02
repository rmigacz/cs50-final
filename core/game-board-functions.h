#ifndef GAMEBOARDFUNCTIONS_H
#define GAMEBOARDFUNCTIONS_H

#include "../ui/Board.h"
#include "../ui/Sprite.h"
#include "../ui/Position.h"

int init_sprites_position(Board *board, Sprite *chinchilla, Sprite **almonds);
int reset_sprites_position(Board *board, Sprite *chinchilla, Sprite **almonds);

#endif
