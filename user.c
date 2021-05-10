#include "game.h"
#include "user.h"

int addScore(Game *s)
{
  getchar();
  ClearScreen();
  draw_map(s);
  gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 5);
  printf("<What's your name?> ");

  scanf("%[^\n]", s->userName);

  gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 6);
  printf("<==> Added!>");
  gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 8);
  printf("<  PRESS ENTER  > ");
  getch();

  return 1;
}

void readScoreBoard(Game s)
{
  printf("%s %5d POINTS\n", s.userName, s.score);
}

int updateScoreBoard(Game *s)
{
  ClearScreen();
  draw_map(s);

  gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 5);
  printf("What's your new name? ");
  getchar();
  scanf("%[^\n]", s->userName);

  gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 8);
  printf("==> YOUR NAME IS UPDATED!\n");
  return 1;
}

int deleteMenu(Game *s)
{
  ClearScreen();
  draw_map(s);

  s->score = -1;
  gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 8);
  printf("==> DELETE COMPLETE!\n");
  return 0;
}
