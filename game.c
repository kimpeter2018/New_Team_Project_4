#include"game.h"
#include"user.h"

void gotoxy(int x,int y,char* s) { //x값을 2x로 변경, 좌표값에 바로 문자열을 입력할 수 있도록 printf함수 삽입  
    COORD pos={2*x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
    printf("%s",s);
}

void title(Game *s){
    int i,j;
    
    while (kbhit()) getch(); //버퍼에 있는 키값을 버림 

    draw_map(s);    //맵 테두리를 그림 
    for(i=MAP_Y+1;i<MAP_Y+MAP_HEIGHT-1;i++){ // 맵 테두리 안쪽을 빈칸으로 채움 
        for(j=MAP_X+1;j<MAP_X+MAP_WIDTH-1;j++) gotoxy(j,i,"  ");
    }

    gotoxy(MAP_X+(MAP_WIDTH/2)-7,MAP_Y+5,"+--------------------------+");
    gotoxy(MAP_X+(MAP_WIDTH/2)-7,MAP_Y+6,"| TEAM PROJECT : S N A K E |");
    gotoxy(MAP_X+(MAP_WIDTH/2)-7,MAP_Y+7,"+--------------------------+");

    gotoxy(MAP_X+(MAP_WIDTH/2)-7,MAP_Y+9," < PRESS ANY KEY TO START > ");

    gotoxy(MAP_X+(MAP_WIDTH/2)-7,MAP_Y+11,"   ◇ ←,→,↑,↓ : Move    ");
    gotoxy(MAP_X+(MAP_WIDTH/2)-7,MAP_Y+12,"   ◇ P : Pause             ");    
    gotoxy(MAP_X+(MAP_WIDTH/2)-7,MAP_Y+13,"   ◇ ESC : Quit              ");    

    gotoxy(MAP_X+(MAP_WIDTH/2)-7,MAP_Y+16,"  21800729 최성찬");
    gotoxy(MAP_X+(MAP_WIDTH/2)-7,MAP_Y+17,"  21800199 김현민");   
    
    while(1){
        if(kbhit()){ //키입력받음 
            s->key=getch();
            if(s->key==ESC) exit(0); // ESC키면 종료 
            else break; //아니면 그냥 계속 진행 
        } 
        gotoxy(MAP_X+(MAP_WIDTH/2)-7,MAP_Y+9," < PRESS ANY KEY TO START > ");
        Sleep(400);
        gotoxy(MAP_X+(MAP_WIDTH/2)-7,MAP_Y+9,"                            ");
        Sleep(400);
        
    }
    reset(s); // 게임을 초기화  
}
 
void reset(Game *s){
    int i;
    system("cls"); //화면을 지움 
    draw_map(s); //맵 테두리를 그림 
    while (kbhit()) getch(); //버퍼에 있는 키값을 버림 
    
    s->dir=LEFT; // 방향 초기화  
    s->speed=100; // 속도 초기화 
    s->length=5; //뱀 길이 초기화 
    s->score=0; //점수 초기화 
    for(i=0;i<s->length;i++){ //뱀 몸통값 입력 
        s->x[i]=MAP_WIDTH/2+i;
        s->y[i]=MAP_HEIGHT/2;
        gotoxy(MAP_X+s->x[i],MAP_Y+s->y[i],"S");
    }
    gotoxy(MAP_X+s->x[0],MAP_Y+s->y[0],"O"); //뱀 머리 그림 
    food(s); // food 생성  
}
 
void draw_map(Game *s){ //맵 테두리 그리는 함수 
    int i,j;
    for(i=0;i<MAP_WIDTH;i++){
        gotoxy(MAP_X+i,MAP_Y,"■");
    }
    for(i=MAP_Y+1;i<MAP_Y+MAP_HEIGHT-1;i++){
        gotoxy(MAP_X,i,"■");
        gotoxy(MAP_X+MAP_WIDTH-1,i,"■");
    }
    for(i=0;i<MAP_WIDTH;i++){
        gotoxy(MAP_X+i,MAP_Y+MAP_HEIGHT-1,"■");
    }
}
 
void move(Game *s, int dir){
    int i;
 
    if(s->x[0]==s->food_x&&s->y[0]==s->food_y){ //food와 충돌했을 경우 
        s->score+=10; //점수 증가 
        food(s); //새로운 food 추가 
        s->length++; //길이증가 
        s->x[s->length-1]=s->x[s->length-2]; //새로만든 몸통에 값 입력 
        s->y[s->length-1]=s->y[s->length-2];
    }
    if(s->x[0]==0||s->x[0]==MAP_WIDTH-1||s->y[0]==0||s->y[0]==MAP_HEIGHT-1){ //벽과 충돌했을 경우 
        game_over(s);
        return; //game_over에서 게임을 다시 시작하게 되면 여기서부터 반복되므로 
                //return을 사용하여 move의 나머지 부분이 실행되지 않도록 합니다. 
    }
    for(i=1;i<s->length;i++){ //자기몸과 충돌했는지 검사 
        if(s->x[0]==s->x[i]&&s->y[0]==s->y[i]){
            game_over(s);
            return;
        }
    }
    
    gotoxy(MAP_X+s->x[s->length-1],MAP_Y+s->y[s->length-1],"  "); //몸통 마지막을 지움 
    for(i=s->length-1;i>0;i--){ //몸통좌표를 한칸씩 옮김 
        s->x[i]=s->x[i-1];
        s->y[i]=s->y[i-1];
    }
    gotoxy(MAP_X+s->x[0],MAP_Y+s->y[0],"S"); //머리가 있던곳을 몸통으로 고침 
    if(dir==LEFT) --s->x[0]; //방향에 따라 새로운 머리좌표(x[0],y[0])값을 변경 
    if(dir==RIGHT) ++s->x[0];
    if(dir==UP) --s->y[0]; 
    if(dir==DOWN) ++s->y[0];     
    gotoxy(MAP_X+s->x[i],MAP_Y+s->y[i],"O"); //새로운 머리좌표값에 머리를 그림 
}
 
void pause(Game *s){ // p키를 눌렀을 경우 게임을 일시 정지 
    while(1){
        if(s->key==PAUSE){
            gotoxy(MAP_X+(MAP_WIDTH/2)-9,MAP_Y,"< PAUSE : PRESS ANY KEY TO RESUME > ");
            Sleep(400);
            gotoxy(MAP_X+(MAP_WIDTH/2)-9,MAP_Y,"                                    ");
            Sleep(400);
        }
        else{
            draw_map(s);
            return;
        } 
        if(kbhit()){
            
                do{
                    s->key=getch();
                }
                while(s->key==224);
        }
            
    }
}
 
void game_over(Game *s){ //게임종료 함수 
    gotoxy(MAP_X+(MAP_WIDTH/2)-6,MAP_Y+5,"+----------------------+");
    gotoxy(MAP_X+(MAP_WIDTH/2)-6,MAP_Y+6,"|      GAME OVER..     |");
    gotoxy(MAP_X+(MAP_WIDTH/2)-6,MAP_Y+7,"+----------------------+");
    gotoxy(MAP_X+(MAP_WIDTH/2)-6,MAP_Y+8," YOUR SCORE : ");
    printf("%d", s->last_score=s->score);
    
    gotoxy(MAP_X+(MAP_WIDTH/2)-7,MAP_Y+12," Press any keys to restart.. ");
    
    if(s->score>s->best_score) {
        s->best_score=s->score;
    gotoxy(MAP_X+(MAP_WIDTH/2)-4,MAP_Y+10,"☆ BEST SCORE ☆");
    }
    Sleep(500);
        while (kbhit()) getch();
    s->key=getch();
    title(s);
}
 
void food(Game *s){
    int i;
    
    int food_crush_on=0;//food가 뱀 몸통좌표에 생길 경우 on 
    int r=0; //난수 생성에 사동되는 변수 
    gotoxy(MAP_X,MAP_Y+MAP_HEIGHT," YOUR SCORE: "); //점수표시 
    printf("%3d, LAST SCORE: %3d, BEST SCORE: %3d", s->score, s->last_score, s->best_score);
    
    while(1){            
        food_crush_on=0;    
        srand((unsigned)time(NULL)+r); //난수표생성 
        s->food_x=(rand()%(MAP_WIDTH-2))+1;    //난수를 좌표값에 넣음 
        s->food_y=(rand()%(MAP_HEIGHT-2))+1;
        
        for(i=0;i<s->length;i++){ //food가 뱀 몸통과 겹치는지 확인  
            if(s->food_x==s->x[i]&&s->food_y==s->y[i]){
                food_crush_on=1; //겹치면 food_crush_on 를 on 
                r++;
break;
            }
        }
        
        if(food_crush_on==1) continue; //겹쳤을 경우 while문을 다시 시작 
            
        gotoxy(MAP_X+s->food_x,MAP_Y+s->food_y,"★"); //안겹쳤을 경우 좌표값에 food를 찍고 
        s->speed-=3; //속도 증가 
        break;
        
    }
}

void status(Game *s){ //각종 스텟을 볼수 있는 함수 
    gotoxy(MAP_X+MAP_WIDTH+1,MAP_Y,"head= ");
    printf("%2d,%2d",s->x[0],s->y[0]);
    gotoxy(MAP_X+MAP_WIDTH+1,MAP_Y+1,"food= ");
    printf("%2d,%2d",s->food_x,s->food_y);
    gotoxy(MAP_X+MAP_WIDTH+1,MAP_Y+2,"leng= ");
    printf("%2d",s->length);
    gotoxy(MAP_X+MAP_WIDTH+1,MAP_Y+3,"key= ");
    printf("%3d",s->key);
    gotoxy(MAP_X+MAP_WIDTH+1,MAP_Y+4,"spd= ");
    printf("%3d",s->speed);
    gotoxy(MAP_X+MAP_WIDTH+1,MAP_Y+6,"score= ");
    printf("%3d",s->score);  
}