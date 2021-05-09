#include "game.h"

void list(Users *u, int count){
    printf("\nName            score\n");
    printf("-----------------------------------\n");
    for(int i = 0; i < count; i ++){
    if(u[i].score == -1) continue;
    printf("%2d ", i+1);
    readScoreBoard(u[i]);
    }
}

int dataNo(Users *u, int count){
    int no;
    list(u, count);
    printf("번호는? (취소: 0)? ");
    scanf("%d", &no);
    
    return no;
}

int selectMenu(){
    int menu;
    printf("\n*** Score Board ***\n");
    printf("1. 조회\n");
    printf("2. 추가\n");
    printf("3. 수정\n");
    printf("4. 삭제\n");
    printf("5. 파일저장\n");
    printf("6. 검색\n");
    printf("7. 게임으로 돌아가기");
    printf("0. 종료\n\n");
    printf("=> 원하는 메뉴는? ");
    scanf("%d", &menu);
    printf("****************\n");

    return menu;
}

void displayMenu(Users *ulist, Game *s, int count){
    int menu;
    int curcount = count;
    while (1)
    {
        menu = selectMenu();
        getchar();
        if (menu == 0)
            break;
        if (menu == 1 || menu == 3 || menu == 4)
        {
            if (count == 0)
            {
                printf(" 데이터가 없습니다!\n");
                continue;
            }
        }

        if (menu == 1)
            list(ulist, curcount);
        else if (menu == 2)
        {
            count += addScore(&ulist[curcount++], s->score);
        }
        else if (menu == 3)
        {
            int no = dataNo(ulist, curcount);
            if (no == 0)
            {
                printf("=>취소됨!");
                continue;
            }
            updateMenu(&ulist[no - 1]);
        }
        else if (menu == 4)
        {
            int no = dataNo(ulist, curcount);
            if (no == 0)
            {
                printf("=>취소됨!");
                continue;
            }
            int deleteok;
            printf("정말로 삭제하시겠습니까?(삭제:1)");
            scanf("%d", &deleteok);
            if (deleteok == 1)
            {
                if (deleteMenu(&ulist[no - 1]))
                    count--;
            }
        }
        // else if (menu == 5)
        // {
        //     if (count == 0)
        //         printf("데이터가 없습니다!\n");
        //     else
        //         saveDa(ulist, curcount);
        // }
        else if (menu == 7)
        {
            title(s);
        }
    }
}