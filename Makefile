CC := gcc
CFLAGS := `sdl2-config --libs --cflags` -lSDL2_ttf -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm

HDRS := graphics/graphics.h include/game-errno.h ui/Window.h ui/Footer.h ui/Board.h ui/Sprite.h ui/Position.h ui/Velocity.h include/game-parameters.h include/game-animation.h include/game-functions.h include/game-board-functions.h
SRCS := graphics/graphics.c src/game.c ui/Window.c ui/Footer.c ui/Board.c ui/Sprite.c src/game-animation.c src/game-functions.c src/game-board-functions.c

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
