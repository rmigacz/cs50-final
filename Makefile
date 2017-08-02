CC := gcc
CFLAGS := `sdl2-config --libs --cflags` -lSDL2_ttf -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm
OBJDIR := obj

HDRS := include/game-errno.h include/game-sdl-utils.h include/Window.h include/Footer.h include/Board.h include/Sprite.h include/Position.h include/Velocity.h include/game-parameters.h include/game-animation.h include/game-functions.h include/game-board-functions.h
SRCS := src/game.c src/game-sdl-utils.c src/Window.c src/Footer.c src/Board.c src/Sprite.c src/game-animation.c src/game-functions.c src/game-board-functions.c

OBJS := $(SRCS:.c=.o)


EXEC := game

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)
	
$(OBJS): $(@:.o=.c) $(HDRS) Makefile
	$(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)
		
clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean
