#include "user.h"

int addScore(Game *s)
{
  printf("What's your name? ");
  scanf("%[^\n]", s->userName);

  printf("==> Ãß°¡µÊ!\n");
  return 1;
}

void readScoreBoard(Game s)
{
  printf("%s %dÁ¡", s.userName, s.score);
}

int updateScoreBoard(Game *s)
{
  printf("What's your new name? ");
  getchar();
  scanf("%[^\n]", s->userName);

  printf("==> ¼öÁ¤µÊ!\n");
  return 1;
}

int deleteMenu(Game *s)
{
  s->score = -1;
  printf("==> »èÁ¦µÊ!\n");
  return 0;
}
