#ifndef GAMEANIMATION_H
#define GAMEANIMATION_H

#include "../board/Board.h"
#include "../ui/Window.h"
#include "../ui/Footer.h"
#include "../ui/Sprite.h"

int animate(Window *window, Footer *footer, Board *board, Sprite *chinchilla,
		Sprite **almonds);

#endif
