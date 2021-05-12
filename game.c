#include "game.h"
#include "user.h"

void gotoxy(int x, int y)
{ //x���� 2x�� ����, ��ǥ���� �ٷ� ���ڿ��� �Է��� �� �ֵ��� printf�Լ� ����
    COORD pos = {2 * x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void ClearScreen()
{
	system("cls");
}

void title(Game *s)
{
    int i, j;

    while (kbhit())
        getch(); //���ۿ� �ִ� Ű���� ����

    draw_map(s); //�� �׵θ��� �׸�
    for (i = MAP_Y + 1; i < MAP_Y + MAP_HEIGHT - 1; i++)
    { // �� �׵θ� ������ ��ĭ���� ä��
        for (j = MAP_X + 1; j < MAP_X + MAP_WIDTH - 1; j++){
            gotoxy(j, i);
            printf("  ");
        }
    }

    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 5);
    printf("+--------------------------+");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 6);
    printf("| TEAM PROJECT : S N A K E |");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 7);
    printf("+--------------------------+");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 9);
    printf("< PRESS ANY KEY TO START >");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 11);
    printf("   �� ��,��,��,�� : Move    ");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 12);
    printf("   �� P : Pause             ");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 13);
    printf("   �� ESC : Quit              ");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 16);
    printf("  21800729 �ּ���            ");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 17);
    printf("  21800199 ������            ");

    while (1)
    {
        if (kbhit())
        { //Ű�Է¹���
            s->key = getch();
            if (s->key == ESC)
                exit(0); // ESCŰ�� ����
            else
                break; //�ƴϸ� �׳� ��� ����
        }
        gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 9);
        printf(" < PRESS ANY KEY TO START > ");
        Sleep(400);
        gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 9);
        printf("                            ");
        Sleep(400);
    }
    reset(s); // ������ �ʱ�ȭ
}

void reset(Game *s)
{
    int i;
    system("cls"); //ȭ���� ����
    draw_map(s);   //�� �׵θ��� �׸�
    while (kbhit())
        getch(); //���ۿ� �ִ� Ű���� ����

    s->dir = LEFT;  // ���� �ʱ�ȭ
    s->speed = 100; // �ӵ� �ʱ�ȭ
    s->length = 5;  //�� ���� �ʱ�ȭ
    s->score = 0;   //���� �ʱ�ȭ
    for (i = 0; i < s->length; i++)
    { //�� ���밪 �Է�
        s->x[i] = MAP_WIDTH / 2 + i;
        s->y[i] = MAP_HEIGHT / 2;
        gotoxy(MAP_X + s->x[i], MAP_Y + s->y[i]);
        printf("S");
    }
    gotoxy(MAP_X + s->x[0], MAP_Y + s->y[0]); //�� �Ӹ� �׸�
    printf("O");
    food(s);                                       // food ����
}

void draw_map()
{ //�� �׵θ� �׸��� �Լ�
    int i;
    for (i = 0; i < MAP_WIDTH; i++)
    {
        gotoxy(MAP_X + i, MAP_Y);
        printf("��");
    }
    for (i = MAP_Y + 1; i < MAP_Y + MAP_HEIGHT - 1; i++)
    {
        gotoxy(MAP_X, i);
        printf("��");
        gotoxy(MAP_X + MAP_WIDTH - 1, i);
        printf("��");
    }
    for (i = 0; i < MAP_WIDTH; i++)
    {
        gotoxy(MAP_X + i, MAP_Y + MAP_HEIGHT - 1);
        printf("��");
    }
}

int move(Game *s, int dir)
{
    int i, menu;

    if (s->x[0] == s->food_x && s->y[0] == s->food_y)
    {                                              //food�� �浹���� ���
        s->score += 10;                            //���� ����
        food(s);                                   //���ο� food �߰�
        s->length++;                               //��������
        s->x[s->length - 1] = s->x[s->length - 2]; //���θ��� ���뿡 �� �Է�
        s->y[s->length - 1] = s->y[s->length - 2];
    }
    if (s->x[0] == 0 || s->x[0] == MAP_WIDTH - 1 || s->y[0] == 0 || s->y[0] == MAP_HEIGHT - 1)
    { //���� �浹���� ���
        game_over(s);
        menu = askRank(s);
        return menu; //game_over���� ������ �ٽ� �����ϰ� �Ǹ� ���⼭���� �ݺ��ǹǷ�
                //return�� ����Ͽ� move�� ������ �κ��� ������� �ʵ��� �մϴ�.
    }

    for (i = 1; i < s->length; i++)
    { //�ڱ���� �浹�ߴ��� �˻�
        if (s->x[0] == s->x[i] && s->y[0] == s->y[i])
        {
            game_over(s);
            menu = askRank(s);
            return menu;
        }
    }

    gotoxy(MAP_X + s->x[s->length - 1], MAP_Y + s->y[s->length - 1]); //���� �������� ����
    printf("  ");
    for (i = s->length - 1; i > 0; i--)
    { //������ǥ�� ��ĭ�� �ű�
        s->x[i] = s->x[i - 1];
        s->y[i] = s->y[i - 1];
    }
    gotoxy(MAP_X + s->x[0], MAP_Y + s->y[0]); //�Ӹ��� �ִ����� �������� ��ħ
    printf("S");
    if (dir == LEFT)
        --s->x[0]; //���⿡ ���� ���ο� �Ӹ���ǥ(x[0],y[0])���� ����
    if (dir == RIGHT)
        ++s->x[0];
    if (dir == UP)
        --s->y[0];
    if (dir == DOWN)
        ++s->y[0];
    gotoxy(MAP_X + s->x[i], MAP_Y + s->y[i]); //���ο� �Ӹ���ǥ���� �Ӹ��� �׸�
    printf("O");
    return 0;
}

void pause(Game *s)
{ // pŰ�� ������ ��� ������ �Ͻ� ����
    while (1)
    {
        if (s->key == PAUSE)
        {
            gotoxy(MAP_X + (MAP_WIDTH / 2) - 9, MAP_Y);
            printf("< PAUSE : PRESS ANY KEY TO RESUME > ");
            Sleep(400);
            gotoxy(MAP_X + (MAP_WIDTH / 2) - 9, MAP_Y);
            printf("                                    ");
            Sleep(400);
        }
        else
        {
            draw_map(s);
            return;
        }
        if (kbhit())
        {

            do
            {
                s->key = getch();
            } while (s->key == 224);
        }
    }
}

void list(Game *s, int count)
{
    ClearScreen();
    draw_map(s);
    
    for (int i = 0; i < count; i++)
    {
        if (s[i].score == -1)
            continue;
        gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 6 + i);
        printf("%2d ", i + 1);
        readScoreBoard(s[i]);
    }

    getch();
}

int dataNo(Game *s, int count)
{
    int no;
    list(s, count);
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 14);
    printf("��ȣ�� (�ּ�: 0)? ");
    scanf("%d", &no);

    return no;
}

void saveDa(Game *s, int count)
{
    FILE *fp;
    fp = fopen("Game.txt", "wt");
    for (int i = 0; i < count; i++)
    {
        if (s[i].score == -1)
            continue;
        fprintf(fp, "%s %d\n", s[i].userName, s[i].score);
    }
    fclose(fp);
    printf("=> �����!\n");
    getch();
}

int loadData(Game *s)
{
    int i = 0;
    FILE *fp;
    fp = fopen("Snake.txt", "rt");
    if (fp == NULL)
    {
        fp = fopen("Snake.txt", "w");
        gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 5);
        printf("+--------------------------+");
        gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 6);
        printf("|        =>���� ����!       |");
        gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 7);
        printf("+--------------------------+");
    }
    else
    {
        fp = fopen("Snake.txt", "rt");
        for (; i < 100; i++)
        {
            fscanf(fp, "%s", s[i].userName);
            if (feof(fp))
                break;
            fscanf(fp, "%d", &s[i].score);
        }
        gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 5);
        printf("+--------------------------+");
        gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 6);
        printf("|        =>�ε� ����!      |");
        gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 7);
        printf("+--------------------------+");
    }
    fclose(fp);
    getch();
    return i;
}

void game_over(Game *s)
{ //�������� �Լ�
    ClearScreen();
    draw_map(s);
    gotoxy(MAP_X+(MAP_WIDTH/2)-6,MAP_Y+5);
    printf("+----------------------+");
    gotoxy(MAP_X+(MAP_WIDTH/2)-6,MAP_Y+6);
    printf("|      GAME OVER..     |");
    gotoxy(MAP_X+(MAP_WIDTH/2)-6,MAP_Y+7);
    printf("+----------------------+");
    gotoxy(MAP_X+(MAP_WIDTH/2)-6,MAP_Y+8);
    printf(" YOUR SCORE : %d", s->last_score=s->score);
    
    gotoxy(MAP_X+(MAP_WIDTH/2)-7,MAP_Y+12);
    printf(" Press any keys to restart.. ");
    
    if(s->score>s->best_score) {
        s->best_score=s->score;
    gotoxy(MAP_X+(MAP_WIDTH/2)-4,MAP_Y+10);
    printf("�� BEST SCORE ��");
    }
    Sleep(500);
        while (kbhit()) getch();
    s->key=getch();
}

void food(Game *s)
{
    int i;

    int food_crush_on = 0;             //food�� �� ������ǥ�� ���� ��� on
    int r = 0;                         //���� ������ �絿�Ǵ� ����
    gotoxy(MAP_X, MAP_Y + MAP_HEIGHT); //����ǥ��
    printf(" YOUR SCORE: %3d, LAST SCORE: %3d, BEST SCORE: %3d", s->score, s->last_score, s->best_score);

    while (1)
    {
        food_crush_on = 0;
        srand((unsigned)time(NULL) + r);            //����ǥ����
        s->food_x = (rand() % (MAP_WIDTH - 2)) + 1; //������ ��ǥ���� ����
        s->food_y = (rand() % (MAP_HEIGHT - 2)) + 1;

        for (i = 0; i < s->length; i++)
        { //food�� �� ����� ��ġ���� Ȯ��
            if (s->food_x == s->x[i] && s->food_y == s->y[i])
            {
                food_crush_on = 1; //��ġ�� food_crush_on �� on
                r++;
                break;
            }
        }

        if (food_crush_on == 1)
            continue; //������ ��� while���� �ٽ� ����

        gotoxy(MAP_X + s->food_x, MAP_Y + s->food_y); //�Ȱ����� ��� ��ǥ���� food�� ���
        printf("��");
        s->speed -= 3;                                //�ӵ� ����
        break;
    }
}

void status(Game *s)
{ //���� ������ ���� �ִ� �Լ�
    gotoxy(MAP_X + MAP_WIDTH + 1, MAP_Y);
    printf("head= %2d,%2d", s->x[0], s->y[0]);
    gotoxy(MAP_X + MAP_WIDTH + 1, MAP_Y + 1);
    printf("food= %2d,%2d", s->food_x, s->food_y);
    gotoxy(MAP_X + MAP_WIDTH + 1, MAP_Y + 2);
    printf("leng= %2d", s->length);
    gotoxy(MAP_X + MAP_WIDTH + 1, MAP_Y + 3);
    printf("key= %3d", s->key);
    gotoxy(MAP_X + MAP_WIDTH + 1, MAP_Y + 4);
    printf("spd= %3d", s->speed);
    gotoxy(MAP_X + MAP_WIDTH + 1, MAP_Y + 6);
    printf("score= %3d", s->score);
}

void startGame(Game *s){
    title(s);
    int count=0;
    
    while(1){
        if(kbhit()) do{s->key=getch();} while(s->key==224); //Ű �Է¹���
        Sleep(s->speed);
        
        switch(s->key){ //�Է¹��� Ű�� �ľ��ϰ� ����  
            case LEFT:
            case RIGHT:
            case UP:
            case DOWN:
                if((s->dir==LEFT&&s->key!=RIGHT)||(s->dir==RIGHT&&s->key!=LEFT)||(s->dir==UP&&s->key!=DOWN)||
                (s->dir==DOWN&&s->key!=UP))//180ȸ���̵��� �����ϱ� ���� �ʿ�. 
                    s->dir=s->key;
                s->key=0; // Ű���� �����ϴ� �Լ��� reset 
            break;
            case PAUSE: // PŰ�� ������ �Ͻ����� 
                pause(s);
            break;
            case 115: //SŰ�� ������ �����ڿ� status�� Ȱ��ȭ ��Ŵ  
                if(s->status_on==0) s->status_on=1;
                else s->status_on=0;
                s->key=0;
                break;
            case ESC: //ESCŰ�� ������ ���α׷� ���� 
                exit(0);
        }
        count = move(s, s->dir);
        
        if(s->status_on==1) status(s); // statusǥ�� 
        if(count == 1) break;
    }
}

int askRank(Game *s){
    int ox;

    ClearScreen();
    draw_map(s);

    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 6);
    printf("+--------------------------+");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 7);
    printf("|           ��ŷ?          |");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 8);
    printf("+--------------------------+");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 9);
    printf("<  PRESS 1 : YES / 0 : NO  >");
    scanf("%d", &ox);

    ClearScreen();
    draw_map(s);

    if (ox == 1){
        return 1;
    }
    else if(ox == 0){
        startGame(s);
        return 0;
    }
    return 0;
}
////////////////////////////////////////////////////////////////

void selectMenu()
{
    draw_map(); //�� �׵θ��� �׸�

    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 5);
    printf("+--------------------------+");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 6);
    printf("|        1. ���� ����      |");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 7);
    printf("|        2. ��ŷ ��ȸ      |");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 8);
    printf("|        3. ��ŷ �߰�      |");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 9);
    printf("|        4. ��ŷ ����      |");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 10);
    printf("|        5. ��ŷ ����      |");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 11);
    printf("|        6. ���� ����      |");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 12);
    printf("|        7. ���� ����      |");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 13);
    printf("+--------------------------+");

    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 15);
    printf(" <  SELECT OPTION TO START  > ");

    while (1)
    {
        if (kbhit())
            break;

        gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 15);
        printf(" <  SELECT OPTION TO START  > ");
        Sleep(400);
        gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 15);
        printf("                              ");
        Sleep(400);
    }
}