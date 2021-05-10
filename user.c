#include "user.h"

int addScore(Game *s)
{
  getchar();
  printf("What's your name? ");
  scanf("%[^\n]", s->userName);

  printf("==> �߰���!\n");
  return 1;
}

void readScoreBoard(Game s)
{
  printf("%s %d��", s.userName, s.score);
}

int updateScoreBoard(Game *s)
{
  printf("What's your new name? ");
  getchar();
  scanf("%[^\n]", s->userName);

  printf("==> ������!\n");
  return 1;
}

int deleteMenu(Game *s)
{
  s->score = -1;
  printf("==> ������!\n");
  return 0;
}
