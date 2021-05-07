#include <stdio.h>
#include <string.h>
#include "user.h"

int addScore(Users *u, int score)
{
  char delim;
  printf("What's your name? ");
  scanf("%[^\n]", u->userName);
  score = u->score;

  return 1;
}

void readScoreBoard(Users u)
{
  printf("%s %d", u.userName, u.score);
}

int updateMenu(Users *u)
{
  printf("What's your new name? ");
  getchar();
  scanf("%[^\n]", u->userName);

  return 1;
}

int deleteMenu(Users *u)
{
  u->score = -1;
  return 1;
}

int selectMenu()
{
  int menu;
  printf("\n*** Score Board ***\n");
  printf("1. 조회\n");
  printf("2. 추가\n");
  printf("3. 수정\n");
  printf("4. 삭제\n");
  printf("5. 파일저장\n");
  printf("6. 검색\n");
  printf("0. 종료\n\n");
  printf("=> 원하는 메뉴는? ");
  scanf("%d", &menu);
  return menu;
}