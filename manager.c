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
    printf("��ȣ��? (���: 0)? ");
    scanf("%d", &no);
    
    return no;
}

int selectMenu(){
    int menu;
    printf("\n*** Score Board ***\n");
    printf("1. ��ȸ\n");
    printf("2. �߰�\n");
    printf("3. ����\n");
    printf("4. ����\n");
    printf("5. ��������\n");
    printf("6. �˻�\n");
    printf("7. �������� ���ư���");
    printf("0. ����\n\n");
    printf("=> ���ϴ� �޴���? ");
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
                printf(" �����Ͱ� �����ϴ�!\n");
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
                printf("=>��ҵ�!");
                continue;
            }
            updateMenu(&ulist[no - 1]);
        }
        else if (menu == 4)
        {
            int no = dataNo(ulist, curcount);
            if (no == 0)
            {
                printf("=>��ҵ�!");
                continue;
            }
            int deleteok;
            printf("������ �����Ͻðڽ��ϱ�?(����:1)");
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
        //         printf("�����Ͱ� �����ϴ�!\n");
        //     else
        //         saveDa(ulist, curcount);
        // }
        else if (menu == 7)
        {
            title(s);
        }
    }
}