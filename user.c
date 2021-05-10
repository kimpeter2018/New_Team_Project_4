#include "game.h"
#include "user.h"

int addScore(Game *s)
{
  getchar();
  gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 5, "<What's your name?> ");

  scanf("%[^\n]", s->userName);

  gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 5, "<==> Added!>");
  return 1;
}

void readScoreBoard(Game s)
{
  printf("%s %d score", s.userName, s.score);
}

int updateScoreBoard(Game *s)
{
  printf("What's your new name? ");
  getchar();
  scanf("%[^\n]", s->userName);

  printf("==> Changed!\n");
  return 1;
}

int deleteMenu(Game *s)
{
  s->score = -1;
  printf("==> Deleted!\n");
  return 0;
}
