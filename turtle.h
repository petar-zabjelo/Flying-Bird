#ifndef TURTLE_H
#define TURTLE_H

#include <stdio.h>

enum {
	BLACK,
	RED,
	GREEN,
	YELLOW,
	BLUE,
	MAGENTA,
	CYAN,
	WHITE
} color;


void pokeChar(int x, int y, char c);
void eraseChar(int x, int y);
void clearScreen();
void setPenColor(int c);
void setBackColor(int c);
void initTurtle();
void exitTurtle();
void setTitle(char *s);
void waitKey(char key);
void printText(int x, int y, char *s);
void left();
void right();

#endif // TURTLE_H
