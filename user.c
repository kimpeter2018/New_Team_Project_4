#include "game.h"
#include "user.h"

int addScore(Game *s)
{
  getchar();
  gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 5, "<What's your name?> ");

  scanf("%[^\n]", s->userName);

  gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 6, "<==> Added!>");
  gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 7, "<  PRESS ENTER  >");
>>>>>>> main
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
