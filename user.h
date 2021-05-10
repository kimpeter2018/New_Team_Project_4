#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
        char userName[20];
        int score;
} Users;


int addScore(Users *u, int score);
void readScoreBoard(Users u);
void readScoreBoard(Users u);
int deleteMenu(Users *u);

#endif