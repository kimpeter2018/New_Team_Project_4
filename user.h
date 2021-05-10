#ifndef USER_H
#define USER_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include<time.h>

#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80
#define PAUSE 112
#define ESC 27

#define MAP_X 3
#define MAP_Y 2
#define MAP_WIDTH 30
#define MAP_HEIGHT 20

typedef struct {
        char userName[20];
        int score;
} Users;


int addScore(Users *u, int score);
void readScoreBoard(Users u);
void readScoreBoard(Users u);
int deleteMenu(Users *u);

#endif