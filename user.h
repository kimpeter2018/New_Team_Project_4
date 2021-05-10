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

typedef struct{
        char userName[20];
    int x[100], y[100]; //x,y 좌표값을 저장 총 100개 
    int food_x, food_y; //food의 좌표값을 저장 
    int length; //몸길이를 기억 
    int speed; //게임 속도 
    int score; //점수 저장  --reset함수에 의해 초기화됨
    int best_score; //최고 점수 저장 --reset함수에 의해 초기화 되지 않음 
    int last_score; //마지막 점수 저장  --reset함수에 의해 초기화 되지 않음
    int dir; //이동방향 저장 
    int key; //입력받은 키 저장 
    int status_on; // 개발자용 status 표시활성화 변수.. 게임중에 S키를 누르면 활성 
} Game;

int addScore(Game *s);
void readScoreBoard(Game s);
int updateScoreBoard(Game *u);
int deleteMenu(Game *u);

#endif