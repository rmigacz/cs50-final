CC := gcc

CFLAGS := `sdl2-config --libs --cflags` -lSDL2_ttf -ggdb3 -O0 --std=c99 -Wall -lSDL2_image -lm

OBJDIR := obj

HDRS := graphics.h
SRCS := graphics.c

OBJS := $(SRCS:.c=.o)

graphics.o: graphics.c graphics.h
	$(CC) $(CFLAGS) -c graphics.c
		
clean:
	rm -f $(OBJS)

.PHONY: all clean
