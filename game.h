#include"user.h"

void title(Game *s); //���� ����ȭ�� 
void reset(Game *s); //������ �ʱ�ȭ 
void draw_map(); // ������ �׵θ��� �׸� 
void move(Game *s, int dir); //��Ӹ��� �̵� 
void pause(Game *s); //�Ͻ����� 
void game_over(Game *s); //���� ������ Ȯ�� 
void food(Game *s); // ���� ���� 
void status(Game *s); // �����ڿ� statusǥ��
//////////////////////////////////////////////////////////////////////
void list(Game *s, int count);
int dataNo(Game *s, int count);
int selectMenu();