CC := gcc
CFLAGS := `sdl2-config --libs --cflags` -lSDL2_ttf -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm

HDRS := graphics/graphics.h ui/Window.h ui/Footer.h ui/Input.h board/Board.h ui/Sprite.h board/Position.h ui/Velocity.h core/game-parameters.h core/game-animation.h core/game-board-functions.h
SRCS := graphics/graphics.c core/game.c ui/Window.c ui/Footer.c ui/Input.c board/Board.c ui/Sprite.c core/game-animation.c core/game-board-functions.c

OBJS := $(SRCS:.c=.o)


EXEC := chinchilla-game

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)
	
$(OBJS): $(@:.o=.c) $(HDRS) Makefile
	$(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)
		
clean:
	rm -f $(EXEC) $(OBJS)

.PHONY: all clean
