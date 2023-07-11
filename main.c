#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "turtle.h"

struct{
    int oldx;
    int oldy;
    int stanje;
    int pravac;             // pravac za animaciju: 1 ili -1
    int x;
    int y;
} flappy;

struct column {
    int x;
    int visina;
    int pravac;
    int vidljiv;            // Ako je 0 => nevidljiv, ako je 1 => vidljiv
};

struct column columns[4];
int score;
int loops;
int lastLoop;
int score;
const int ymax=30;
const int xmax=70;

int getRandom(int min, int max){
    return min + ((max - min) * rand() / RAND_MAX);
}

void initColumns(){
    for(int i = 0; i < 4; i++) {
        columns[i].x       = 0;
        columns[i].pravac  = 0;
        columns[i].visina  = 0;
        columns[i].vidljiv = 0;
    }
}
void startScreen(){
    printText(50,18,"press space to start");
    printText(10,1,"version:1.0");
    printText(10,2,"creator:silentxshone69");
    printText(10,3,"youtube:xsilentSONE q");
    printText(10,4,"flappy bird copied me :(");
    printText(48,17,"*");
    printText(48,20,"*");
    printText(71,17,"*");
    printText(71,20,"*");
    pokeChar(2,28,':');
    pokeChar(3,28,'0');
    pokeChar(1,28,'[');
    pokeChar(2,26,'|');
    pokeChar(2,25,':');
    pokeChar(3,25,'(');
    pokeChar(1,25,'{');
    pokeChar(5,25,'<');
    printText(6,28,"flappy bird");
    pokeChar(5,28,'<');
    printText(6,25,"me");
    waitKey(' ');
    clearScreen();
}
int detectCollision(){
    struct column *col;

    for(int i; i < 4; i++) {
        col = &columns[i];
        if (col->vidljiv == 1) {
            for(int dio=0; dio <= 1; dio++) {
                int posx = flappy.oldx + dio;
                if ((col->x <= posx)&&(posx <= (col->x+3))) {
                    if (col->pravac == 1) {
                        if (flappy.oldy <= col->visina) return 1;
                    }
                    else {
                        if (flappy.oldy >= (ymax - col->visina)) return 1;
                    }
                }
            }
        }
    }
    return 0;
}

void generateColumns(){
    if((loops - lastLoop) > getRandom(40, 60)) {
        struct column *col;
        for(int i; i < 4; i++){
            col = &columns[i];
            if (col->vidljiv == 0) {
                col->vidljiv = 1;
                col->x = xmax;
                col->visina = getRandom(5, ymax - 5);
                col->pravac = (getRandom(1, 3) < 2) ? 1 : 2;
                lastLoop = loops;
                break;
            }
        }
    }
}

void drawFlappy(int x, int y){
    for(int br=-1; br<=1; br++)
        pokeChar(flappy.oldx + br, flappy.oldy, ' ');

    switch(flappy.stanje){
        case 1:
            pokeChar(x,y,'O');
            pokeChar(x-1,y,'\\');
            pokeChar(x+1,y,'/');
        break;
        case 2:
            pokeChar(x,y,'O');
            pokeChar(x-1,y,'-');
            pokeChar(x+1,y,'-');
        break;
        case 3:
            pokeChar(x,y,'O');
            pokeChar(x-1,y,'/');
            pokeChar(x+1,y,'\\');
        break;
    }

    flappy.oldx = x;
    flappy.oldy = y;

    if(flappy.stanje==3) flappy.pravac = -1;
    if(flappy.stanje==1) flappy.pravac =  1;
    if((loops%5)==0)
        flappy.stanje = flappy.stanje + flappy.pravac;
}

void drawColumn(int x,int visina,int pravac,int mode){
    char zid, krov_dolje, krov_gore;

    if (mode == 1) {
        zid = '|';
        krov_dolje = '_';
        krov_gore  = '-';
    } else {
        zid = ' ';
        krov_dolje = ' ';
        krov_gore  = ' ';
    }

    if(pravac==1){
        for(int br=0; br<=visina; br++){
            pokeChar(x,br,zid);
            pokeChar(x+3,br,zid);
        }
        pokeChar(x+1,visina,krov_dolje);
        pokeChar(x+2,visina,krov_dolje);
    }
    if(pravac==2){
        for(int br=ymax; br>=ymax-visina; br--){
            pokeChar(x,br,zid);
            pokeChar(x+3,br,zid);
        }
        pokeChar(x+1,ymax-visina,krov_gore);
        pokeChar(x+2,ymax-visina,krov_gore);
    }
}

void drawAllColumns() {
    //if ((loops%5) == 0) {
        struct column *col;
        for(int i = 0; i < 4; i++){
            col = &columns[i];
            if (col->vidljiv == 1) {
                drawColumn(col->x, col->visina, col->pravac, 0);
                col->x--;
                if (col->x < 0){
                    score++;
                    col->vidljiv = 0;
                }
                else
                    drawColumn(col->x, col->visina, col->pravac, 1);
            }
        }
    //}
}

void initGame(){
    score=0;
    flappy.oldx=0;
    flappy.oldy=0;
    flappy.stanje=1;
    flappy.pravac=1;
    loops=0;
    lastLoop=0;
    flappy.x=20;
    flappy.y=25;
    loops=0;
    lastLoop=0;

    initColumns();
}

int main(){
    int again=0;
    char ch;

    initTurtle();
    setTitle("ptica na put ka steroidima");

    startScreen();
    initGame();

    while(1){
        Sleep(20);
        generateColumns();
        drawFlappy(flappy.x,flappy.y);
        drawAllColumns();
        if(kbhit()){
            ch=getch();
            if((ch=='w')&&(flappy.y > 0))
                flappy.y--;
            if((ch=='s')&&(flappy.y < ymax))
                flappy.y++;
            if(ch==' ')
                break;
        }
        if (detectCollision() == 1) {
            char buffer[20];
            sprintf(buffer, "score: %03d",score);
            printText(72, 1, buffer);
            printText(72, 2, "PRESS SPACE TO PLAY AGAIN");
            printText(72, 3, "PRESS ENTER TO FINISH");
            again = 0;
            while(again==0){
                Sleep(100);
                if (kbhit()) {
                    switch (getch()) {
                        case ' ':
                            clearScreen();
                            initGame();
                            again = 1;
                            break;
                        case '\r':
                            exitTurtle();
                            return 0;
                        break;
                    }
                }
            }
        }
        loops++;
    }

    //getchar();
    exitTurtle();
    return 0;
}
