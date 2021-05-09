#include "user.h"

int addScore(Users *u, int score)
{
  char delim;
  printf("What's your name? ");
  scanf("%[^\n]", u->userName);
  delim = getchar();
  score = u->score;

  printf("==> 추가됨!\n");
  return 1;
}

void readScoreBoard(Users u)
{
  printf("%s %d점", u.userName, u.score);
}

int updateMenu(Users *u)
{
  printf("What's your new name? ");
  getchar();
  scanf("%[^\n]", u->userName);

  printf("==> 수정됨!\n");
  return 1;
}

int deleteMenu(Users *u)
{
  u->score = -1;
  printf("==> 삭제됨!\n");
  return 0;
}
