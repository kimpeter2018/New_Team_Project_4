#include "game.h"
#include "user.h"

////////////////////////////MAIN START//////////////////////////////
int main()
{
    Game slist[100];
    int rank[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int index = 0;
    int count = 0;
    int menu, no;

    count = loadData(slist);
    index = count;

    while (1)
    {
        ClearScreen();
        selectMenu();
        scanf("%d", &menu);

        switch (menu)
        {
        case 1:
            startGame(slist, rank);
            break;
        case 2:
            ClearScreen();
            if (count > 0)
            {
                list(slist, index);
                break;
            }
            else
            {
                gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 5);
                printf("+--------------------------+");
                gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 6);
                printf("|    =>데이터가 없습니다.   |");
                gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 7);
                printf("+--------------------------+");
                break;
            }
        case 3:
            count += addScore(&slist[index++]);
            break;
        case 4:
            no = dataNo(slist, index);
            if (no == 0)
            {
                gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 5);
                printf("+--------------------------+");
                gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 6);
                printf("|        => 취소됨!        |");
                gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 7);
                printf("+--------------------------+");
                continue;
            }
            updateScoreBoard(&slist[no - 1]);
            break;
        case 5:
            no = dataNo(slist, index);
            ClearScreen();
            draw_map(slist);
            if (no == 0)
            {
                gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 5);
                printf("+--------------------------+");
                gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 6);
                printf("|        => 취소됨!        |");
                gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 7);
                printf("+--------------------------+");
                continue;
            }
            int deleteok;
            gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 5);
            printf("+--------------------------+");
            gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 6);
            printf("| 삭제하시겠습니까?(삭제:1)|");
            gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 7);
            printf("+--------------------------+");
            gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 9);
            printf("<  PRESS 1 : YES / 0 : NO  >");
            scanf("%d", &deleteok);

            if (deleteok == 1)
            {
                if (deleteMenu(&slist[no - 1]))
                    count--;
            }
            break;
        case 6:
            saveDa(slist, count);
            gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 5);
            printf("+--------------------------+");
            gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 6);
            printf("|        => 저장됨!        |");
            gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 7);
            printf("|=> PRESS ANY KEY TO CONTINUE|");
            gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 8);
            printf("+--------------------------+");
            char key;
            scanf("%c", &key);
            break;
        case 7:
            printf("게임을 종료합니다...\n");
            return 0;
        default:
            break;
        }
    }

    return 0;
}
///////////////////////////MAIN END////////////////////////////////