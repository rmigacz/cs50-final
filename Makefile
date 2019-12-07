CC := gcc
CFLAGS := `sdl2-config --libs --cflags` -lSDL2_ttf --std=c99 -Wall -lSDL2_image -lm

HDRS := graphics/graphics.h \
 board/Board.h \
 board/Position.h \
 ui/Footer.h \
 ui/Input.h \
 ui/Sprite.h \
 ui/Velocity.h \
 ui/Window.h \
 core/game-animation.h \
 core/game-board-functions.h \
 core/game-parameters.h \

SRCS := graphics/graphics.c \
 board/Board.c \
 ui/Footer.c \
 ui/Input.c \
 ui/Sprite.c \
 ui/Window.c \
 core/game-animation.c \
 core/game-board-functions.c \
 core/game.c \

OBJS := $(SRCS:.c=.o)

EXEC := game

all: $(EXEC)

$(EXEC): $(OBJS) $(HDRS) Makefile
	$(CC) -o $@ $(OBJS) $(CFLAGS)
	
$(OBJS): $(@:.o=.c) $(HDRS) Makefile
	$(CC) -o $@ $(@:.o=.c) -c $(CFLAGS)
		
clean:
	rm -f $(EXEC) $(OBJS)