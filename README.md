# Chinchilla, the Almonds Eater

## This is the final project for online course CS50: Introduction to Computer Science.
## https://www.edx.org/course/introduction-computer-science-harvardx-cs50x

The project is a 2D game in which you are becoming a Chinchilla and you have to
eat as many almonds as possible in a certain period of time.

![GameGif](https://raw.githubusercontent.com/rmigacz/cs50-final/assets/gameplay.gif)

It is an attempt of rewriting the first project from the course made in Scratch: <br/>
https://scratch.mit.edu/projects/54065950/ </br>
Inspired by seminar *Writing 2D Games in C using SDL*: </br>
http://cs50.tv/2015/fall/#seminars

## Technologies used
- [C language](https://en.wikipedia.org/wiki/C_(programming_language))
- [GCC](https://gcc.gnu.org/)
- [make](https://www.gnu.org/software/make/)
- [SDL 2.0](https://www.libsdl.org/index.php)

## Project structure & description
### Modules
The project consists of 5 main folders (modules):
- **board** - responsible for tracking game elements position,
- **core** - main module with core game logic; depends on the all other modules,
- **graphics** - encapsulates creation of SDL-related elements, e.g. *SDL_Window*, *SDL_Texture*,
- **resources** - contains fonts and picutres used in game,
- **ui** - consists of game elements like *Window*, *Sprite*; depends on graphics module.

<pre>
.
├── board
│   ├── Board.c
│   ├── Board.h
│   └── Position.h
├── core
│   ├── game-animation.c
│   ├── game-animation.h
│   ├── game-board-functions.c
│   ├── game-board-functions.h
│   ├── game.c
│   └── game-parameters.h
├── graphics
│   ├── graphics.c
│   └── graphics.h
├── Makefile
├── README.md
├── resources
│   ├── fonts
│   │   └── DroidSans.ttf
│   └── pics
│       ├── almond.png
│       └── chinchilla.png
└── ui
    ├── Footer.c
    ├── Footer.h
    ├── Input.c
    ├── Input.h
    ├── Sprite.c
    ├── Sprite.h
    ├── Velocity.h
    ├── Window.c
    └── Window.h
</pre>

### Classes

Files which names start with upper case letter could be interpreted as a pseudo classes.
Chinchilla and each almond are a type of **Sprite**, **Board** contains information which 
**Field** is free or not in the **Window**, ect.

### Animation

The core part of the game is placed in a **core** module. It contains different functions, 
among others, functions responsible for moving the Chinchilla in the Window or detecting 
Sprites collision. The main game loop is a part of the **animate** function, placed
in the **game-animation.c** file.

### Board

The idea of the **Board** "class" was to simplify tracking the Sprites positions.

The **Board** contains information about game **fields** (two dimensional array of integers). 
As a **field** we understand the part of a **Window** with assigned number of **row** (the array row number)
and **column** (the array column number) and **information whether the part is taken** 
(element of the array) by the game **Sprite**.

In the **game-parameters.h** file, global variables are defined including:
- **Window** dimension (equal width and height)
- **Field** dimension (equal width and height)
- **Board** parameters:
	- width and height
	- rows and columns (fields) count
- **Sprites** parameters:
	- width and height
	- rows and columns (fields) count

**Almond** Sprite takes one field (one row, one column) and **Chinchilla** Sprite takes 20 fields
(5 rows and 4 columns). Below is presented example of **Board** state - Chinchilla's top left 
field is **I12** and some Almonds are located at **D16**, **R1**, **O14**.

|    | A | B | C | D | E | F | G | H | I | J | K | L | M | N | O | P | R |
|----|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| 17 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
| 16 |   |   |   | * |   |   |   |   |   |   |   |   |   |   |   |   |   |
| 15 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
| 14 |   |   |   |   |   |   |   |   |   |   |   |   |   |   | * |   |   |
| 13 |   | * |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
| 12 |   |   |   |   |   |   |   |   | # | # | # | # |   |   |   |   |   |
| 11 |   |   |   |   |   |   |   |   | # | # | # | # |   |   |   |   |   |
| 10 |   |   |   |   |   |   |   |   | # | # | # | # |   |   |   |   | * |
| 9  |   |   |   |   |   |   |   |   | # | # | # | # |   |   |   |   |   |
| 8  |   |   |   |   |   |   |   |   | # | # | # | # |   |   |   |   |   |
| 7  |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
| 6  |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
| 5  |   |   |   | * |   |   |   |   | * |   |   |   | * |   |   |   |   |
| 4  |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
| 3  |   | * |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
| 2  |   |   |   |   |   |   | * |   |   |   |   |   |   |   |   |   |   |
| 1  |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   | * |

## Game algorithm
1. Initialize game objects - Window, Board, Sprites, ect.
2. Draw Sprites positions.
3. Begin animation loop - while CLOSED_REQUEST is not detected and TIME value is less than TIME_LIMIT
	1. Detect pressed key by player
	2. Determine Chinchilla velocity
	3. Determine new Chinchilla position
	4. Check if Chinchilla collided with specified Window (Board) bounds
	5. Check if Chinchilla collided with Almond - if true
		1. Increment value of eaten Almonds (score)
		2. Clear Board
		3. Reset all Sprites positions
	6. Else
		1. Set only new Chinchilla position
	7. Clear Window
	8. Add Chinchilla to Window with determined before position
	9. Add Almonds to Window with determined before position
	10. Update Footer's message: update score and time
	11. Update Window's content.
4. Free allocated memory - cleanup.
5. Close program.

## What could be improved or added
1. Rules from Makefile: exec and .o files could be generated in separate directories, for example /objs and /bin.
2. Relative paths of header files included in the source files could be removed - "../include/game-functions.h".
3. Drawing Almonds positions algorithm - at this moment the positions are too close to the Chinchilla position.
4. Exception handling.
5. Game menu.
6. Tests.
