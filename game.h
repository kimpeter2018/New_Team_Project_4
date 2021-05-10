#include"user.h"

void title(Game *s); //게임 시작화면 
void reset(Game *s); //게임을 초기화 
void draw_map(); // 게임판 테두리를 그림 
void move(Game *s, int dir); //뱀머리를 이동 
void pause(Game *s); //일시정지 
void game_over(Game *s); //게임 오버를 확인 
void food(Game *s); // 음식 생성 
void status(Game *s); // 개발자용 status표시
//////////////////////////////////////////////////////////////////////
void list(Game *s, int count);
int dataNo(Game *s, int count);
int selectMenu();