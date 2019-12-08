# Chinchilla, the Almonds Eater

## This is the final project for online course CS50: Introduction to Computer Science.
## https://www.edx.org/course/introduction-computer-science-harvardx-cs50x

The project is a 2D game in which you are becoming a Chinchilla and you have to
eat as many almonds as possible in a certain period of time.

![GameGif](https://raw.githubusercontent.com/rmigacz/cs50-final/assets/cs50-final-state-gameplay.gif)

It is an attempt of rewriting the first project from the course made in Scratch: <br/>
https://scratch.mit.edu/projects/54065950/ </br>
inspired by seminar "Writing 2D Games in C using SDL": </br>
http://cs50.tv/2015/fall/#seminars

## The main targets of creating Chinchilla The Almonds Eater game
1. Learn more about programming in C language by writing a relatively simple game
2. Writing it according to the common Clean Code rules
3. Complete the course :)

## Technologies used, development environment
The game is written in C language with SDL library. It has been made in Eclipse IDE,
Neon 2, release 4.6.2 in Ubuntu MATE 16.04.2 LTS. The project is being built with
dedicated Makefile.

## Project structure and description of the most important parts
### Projects modules
The project consists of three main folders (modules):
- include - contains header files,
- resources - contains fonts and picutres used in game,
- src - source files which implement "interfaces" from the
include folder.

<pre>
.
├── include
│   ├── Board.h
│   ├── Footer.h
│   ├── game-animation.h
│   ├── game-board-functions.h
│   ├── game-errno.h
│   ├── game-functions.h
│   ├── game-parameters.h
│   ├── game-sdl-utils.h
│   ├── Position.h
│   ├── Sprite.h
│   ├── Velocity.h
│   └── Window.h
├── Makefile
├── resources
│   ├── fonts
│   │   └── DroidSans.ttf
│   └── pics
│       ├── almond.png
│       └── chinchilla.png
└── src
    ├── Board.c
    ├── Footer.c
    ├── game-animation.c
    ├── game-board-functions.c
    ├── game.c
    ├── game-functions.c
    ├── game-sdl-utils.c
    ├── Sprite.c
    └── Window.c
</pre>

### Objects

Files which names start with upper case letter should be interpreted as an objects.
Chinchilla and each almond are a type of Sprite, Board contains information which 
Field is free or not in the Window, ect.

### Animation

The core part of the game is placed in a game-animation file. It contains different functions, among others, functions
responsible for moving the Chinchilla in the Window, detecting Sprites collision.

### Board

The game-animation uses the Board object. The idea of using it was to simplify 
setting the Sprites positions.
The Board contains a two-dimensional array of game fields. As a field we understand
the part of a Window with assigned number of row and column and information whether
the part is taken by the game Sprite. </br></br>
In the game-parameters file global variables are defined including Window dimensions,
Field dimension, and row and column Sprites fields count. Almond
takes one field (one row, one column) and Chinchilla takes 5 rows and 4 columns.
Below is presented example of Board state - Chinchilla's top left field is I12
and some Almonds are located at D16, R1, O14.

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
