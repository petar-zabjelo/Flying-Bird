#include <stdio.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "turtle.h"

void pokeChar(int x, int y, char c) {
    printf("\x1b[%d;%dH%c", y + 1, x + 1, c);
}

void eraseChar(int x, int y) {
    printf("\x1b[%d;%dH%c", y + 1, x + 1, ' ');
}

void clearScreen() {
    printf("\x1b[2J");
}

void setPenColor(int c) {
	printf("\x1b[%dm", 30 + c);
}

void setBackColor(int c) {
	printf("\x1b[%dm", 40 + c);
}

void setTitle(char *s){
    printf("\x1b]0;%s\x1b\x5c", s);
}

void printText(int x, int y, char *s) {
    while(*s != 0){pokeChar(x++, y, *s++);};
}

void waitKey(char key){
    while(1) {
        while(!kbhit()){Sleep(100);}
        if (getch() == key) break;
    }
}

void initTurtle() {
    srand(time(NULL));

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole != INVALID_HANDLE_VALUE) {
       DWORD mode = 0;
       if (GetConsoleMode(hConsole, &mode)) {
          mode |=0x0004;
          SetConsoleMode(hConsole, mode);
       }
    }

    clearScreen();
    printf("\x1b[?25l"); // Hide cursor
}

void exitTurtle() {
    setPenColor(WHITE);
    setBackColor(BLACK);
    clearScreen();
    printf("\x1b[?25h"); // Show cursor
}

void left() {
    pokeChar(0, 0, '<');
}

void right() {
    pokeChar(0, 0, '>');
}
