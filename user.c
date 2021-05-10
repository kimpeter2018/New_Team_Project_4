#include "user.h"

int addScore(Users *u, Game *s, int score)
{
  printf("What's your name? ");
  scanf("%[^\n]", u->userName);
  score = s->score;

  printf("==> 추가됨!\n");
  return 1;
}

void readScoreBoard(Users u, Game s)
{
  printf("%s %d점", u.userName, s.score);
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
