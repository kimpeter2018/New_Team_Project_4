#include "user.h"

int addScore(Game *s)
{
  getchar();
  printf("What's your name? ");
  scanf("%[^\n]", s->userName);

  printf("==> ADDED SUCCESSFULLY!\n");
  return 1;
}

void readScoreBoard(Game s)
{
  printf("%s %5dPOINTS", s.userName, s.score);
}

int updateScoreBoard(Game *s)
{
  printf("What's your new name? ");
  getchar();
  scanf("%[^\n]", s->userName);

  printf("==> YOUR NAME IS UPDATED!\n");
  return 1;
}

int deleteMenu(Game *s)
{
  s->score = -1;
  printf("==> DELETE COMPLETE!\n");
  return 0;
}
