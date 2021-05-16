#include"user.h"

void title(Game *s); //���� ����ȭ�� 
void reset(Game *s); //������ �ʱ�ȭ 
void draw_map(); // ������ �׵θ��� �׸� 
int move(Game *s, int dir); //��Ӹ��� �̵� 
void pause(Game *s); //�Ͻ����� 
void game_over(Game *s); //���� ������ Ȯ�� 
void food(Game *s); // ���� ���� 
void status(Game *s); // �����ڿ� statusǥ��
void startGame(Game *s, int *rank); //���� ����
int askRank(Game *s); //��ũ ����
void gotoxy(int x, int y); // xy��
void ClearScreen();
//////////////////////////////////////////////////////////////////////
void list(Game *s, int count);
int dataNo(Game *s, int count);
void saveDa(Game *s, int count);
int loadData(Game *s);
void selectMenu();