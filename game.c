#include "game.h"
#include "user.h"

void gotoxy(int x, int y)
{ //x값을 2x로 변경, 좌표값에 바로 문자열을 입력할 수 있도록 printf함수 삽입
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
        getch(); //버퍼에 있는 키값을 버림

    draw_map(s); //맵 테두리를 그림
    for (i = MAP_Y + 1; i < MAP_Y + MAP_HEIGHT - 1; i++)
    { // 맵 테두리 안쪽을 빈칸으로 채움
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
    printf("   ◇ ←,→,↑,↓ : Move    ");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 12);
    printf("   ◇ P : Pause             ");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 13);
    printf("   ◇ ESC : Quit              ");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 16);
    printf("  21800729 최성찬            ");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 17);
    printf("  21800199 김현민            ");

    while (1)
    {
        if (kbhit())
        { //키입력받음
            s->key = getch();
            if (s->key == ESC)
                exit(0); // ESC키면 종료
            else
                break; //아니면 그냥 계속 진행
        }
        gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 9);
        printf(" < PRESS ANY KEY TO START > ");
        Sleep(400);
        gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 9);
        printf("                            ");
        Sleep(400);
    }
    reset(s); // 게임을 초기화
}

void reset(Game *s)
{
    int i;
    system("cls"); //화면을 지움
    draw_map(s);   //맵 테두리를 그림
    while (kbhit())
        getch(); //버퍼에 있는 키값을 버림

    s->dir = LEFT;  // 방향 초기화
    s->speed = 100; // 속도 초기화
    s->length = 5;  //뱀 길이 초기화
    s->score = 0;   //점수 초기화
    for (i = 0; i < s->length; i++)
    { //뱀 몸통값 입력
        s->x[i] = MAP_WIDTH / 2 + i;
        s->y[i] = MAP_HEIGHT / 2;
        gotoxy(MAP_X + s->x[i], MAP_Y + s->y[i]);
        printf("S");
    }
    gotoxy(MAP_X + s->x[0], MAP_Y + s->y[0]); //뱀 머리 그림
    printf("O");
    food(s);                                       // food 생성
}

void draw_map()
{ //맵 테두리 그리는 함수
    int i;
    for (i = 0; i < MAP_WIDTH; i++)
    {
        gotoxy(MAP_X + i, MAP_Y);
        printf("■");
    }
    for (i = MAP_Y + 1; i < MAP_Y + MAP_HEIGHT - 1; i++)
    {
        gotoxy(MAP_X, i);
        printf("■");
        gotoxy(MAP_X + MAP_WIDTH - 1, i);
        printf("■");
    }
    for (i = 0; i < MAP_WIDTH; i++)
    {
        gotoxy(MAP_X + i, MAP_Y + MAP_HEIGHT - 1);
        printf("■");
    }
}

int move(Game *s, int dir)
{
    int i, menu;

    if (s->x[0] == s->food_x && s->y[0] == s->food_y)
    {                                              //food와 충돌했을 경우
        s->score += 10;                            //점수 증가
        food(s);                                   //새로운 food 추가
        s->length++;                               //길이증가
        s->x[s->length - 1] = s->x[s->length - 2]; //새로만든 몸통에 값 입력
        s->y[s->length - 1] = s->y[s->length - 2];
    }
    if (s->x[0] == 0 || s->x[0] == MAP_WIDTH - 1 || s->y[0] == 0 || s->y[0] == MAP_HEIGHT - 1)
    { //벽과 충돌했을 경우
        game_over(s);
        menu = askRank(s);
        return menu; //game_over에서 게임을 다시 시작하게 되면 여기서부터 반복되므로
                //return을 사용하여 move의 나머지 부분이 실행되지 않도록 합니다.
    }

    for (i = 1; i < s->length; i++)
    { //자기몸과 충돌했는지 검사
        if (s->x[0] == s->x[i] && s->y[0] == s->y[i])
        {
            game_over(s);
            menu = askRank(s);
            return menu;
        }
    }

    gotoxy(MAP_X + s->x[s->length - 1], MAP_Y + s->y[s->length - 1]); //몸통 마지막을 지움
    printf("  ");
    for (i = s->length - 1; i > 0; i--)
    { //몸통좌표를 한칸씩 옮김
        s->x[i] = s->x[i - 1];
        s->y[i] = s->y[i - 1];
    }
    gotoxy(MAP_X + s->x[0], MAP_Y + s->y[0]); //머리가 있던곳을 몸통으로 고침
    printf("S");
    if (dir == LEFT)
        --s->x[0]; //방향에 따라 새로운 머리좌표(x[0],y[0])값을 변경
    if (dir == RIGHT)
        ++s->x[0];
    if (dir == UP)
        --s->y[0];
    if (dir == DOWN)
        ++s->y[0];
    gotoxy(MAP_X + s->x[i], MAP_Y + s->y[i]); //새로운 머리좌표값에 머리를 그림
    printf("O");
    return 0;
}

void pause(Game *s)
{ // p키를 눌렀을 경우 게임을 일시 정지
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
    printf("번호는 (최소: 0)? ");
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
    printf("=> 저장됨!\n");
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
        printf("|        =>파일 없음!       |");
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
        printf("|        =>로딩 성공!      |");
        gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 7);
        printf("+--------------------------+");
    }
    fclose(fp);
    getch();
    return i;
}

void game_over(Game *s)
{ //게임종료 함수
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
    printf("☆ BEST SCORE ☆");
    }
    Sleep(500);
        while (kbhit()) getch();
    s->key=getch();
}

void food(Game *s)
{
    int i;

    int food_crush_on = 0;             //food가 뱀 몸통좌표에 생길 경우 on
    int r = 0;                         //난수 생성에 사동되는 변수
    gotoxy(MAP_X, MAP_Y + MAP_HEIGHT); //점수표시
    printf(" YOUR SCORE: %3d, LAST SCORE: %3d, BEST SCORE: %3d", s->score, s->last_score, s->best_score);

    while (1)
    {
        food_crush_on = 0;
        srand((unsigned)time(NULL) + r);            //난수표생성
        s->food_x = (rand() % (MAP_WIDTH - 2)) + 1; //난수를 좌표값에 넣음
        s->food_y = (rand() % (MAP_HEIGHT - 2)) + 1;

        for (i = 0; i < s->length; i++)
        { //food가 뱀 몸통과 겹치는지 확인
            if (s->food_x == s->x[i] && s->food_y == s->y[i])
            {
                food_crush_on = 1; //겹치면 food_crush_on 를 on
                r++;
                break;
            }
        }

        if (food_crush_on == 1)
            continue; //겹쳤을 경우 while문을 다시 시작

        gotoxy(MAP_X + s->food_x, MAP_Y + s->food_y); //안겹쳤을 경우 좌표값에 food를 찍고
        printf("★");
        s->speed -= 3;                                //속도 증가
        break;
    }
}

void status(Game *s)
{ //각종 스텟을 볼수 있는 함수
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
        if(kbhit()) do{s->key=getch();} while(s->key==224); //키 입력받음
        Sleep(s->speed);
        
        switch(s->key){ //입력받은 키를 파악하고 실행  
            case LEFT:
            case RIGHT:
            case UP:
            case DOWN:
                if((s->dir==LEFT&&s->key!=RIGHT)||(s->dir==RIGHT&&s->key!=LEFT)||(s->dir==UP&&s->key!=DOWN)||
                (s->dir==DOWN&&s->key!=UP))//180회전이동을 방지하기 위해 필요. 
                    s->dir=s->key;
                s->key=0; // 키값을 저장하는 함수를 reset 
            break;
            case PAUSE: // P키를 누르면 일시정지 
                pause(s);
            break;
            case 115: //S키를 누르면 개발자용 status를 활성화 시킴  
                if(s->status_on==0) s->status_on=1;
                else s->status_on=0;
                s->key=0;
                break;
            case ESC: //ESC키를 누르면 프로그램 종료 
                exit(0);
        }
        count = move(s, s->dir);
        
        if(s->status_on==1) status(s); // status표시 
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
    printf("|           랭킹?          |");
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
    draw_map(); //맵 테두리를 그림

    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 5);
    printf("+--------------------------+");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 6);
    printf("|        1. 게임 시작      |");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 7);
    printf("|        2. 랭킹 조회      |");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 8);
    printf("|        3. 랭킹 추가      |");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 9);
    printf("|        4. 랭킹 수정      |");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 10);
    printf("|        5. 랭킹 삭제      |");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 11);
    printf("|        6. 파일 저장      |");
    gotoxy(MAP_X + (MAP_WIDTH / 2) - 7, MAP_Y + 12);
    printf("|        7. 게임 종료      |");
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