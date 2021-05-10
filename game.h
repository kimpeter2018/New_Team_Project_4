#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>
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
    int x[100], y[100]; //x,y ��ǥ���� ���� �� 100�� 
    int food_x, food_y; //food�� ��ǥ���� ���� 
    int length; //�����̸� ��� 
    int speed; //���� �ӵ� 
    int score; //���� ����  --reset�Լ��� ���� �ʱ�ȭ��
    int best_score; //�ְ� ���� ���� --reset�Լ��� ���� �ʱ�ȭ ���� ���� 
    int last_score; //������ ���� ����  --reset�Լ��� ���� �ʱ�ȭ ���� ����
    int dir; //�̵����� ���� 
    int key; //�Է¹��� Ű ���� 
    int status_on; // �����ڿ� status ǥ��Ȱ��ȭ ����.. �����߿� SŰ�� ������ Ȱ�� 
} Game;

void title(Game *s); //���� ����ȭ�� 
void reset(Game *s); //������ �ʱ�ȭ 
void draw_map(Game *s); // ������ �׵θ��� �׸� 
void move(Game *s, int dir); //��Ӹ��� �̵� 
void pause(Game *s); //�Ͻ����� 
void game_over(Game *s); //���� ������ Ȯ�� 
void food(Game *s); // ���� ���� 
void status(Game *s); // �����ڿ� statusǥ��  