#include"game.h"

void gotoxy(int x,int y,char* s) { //x���� 2x�� ����, ��ǥ���� �ٷ� ���ڿ��� �Է��� �� �ֵ��� printf�Լ� ����  
    COORD pos={2*x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
    printf("%s",s);
}

void title(Game *s){
    int i,j;
    
    while (kbhit()) getch(); //���ۿ� �ִ� Ű���� ���� 

    draw_map(s);    //�� �׵θ��� �׸� 
    for(i=MAP_Y+1;i<MAP_Y+MAP_HEIGHT-1;i++){ // �� �׵θ� ������ ��ĭ���� ä�� 
        for(j=MAP_X+1;j<MAP_X+MAP_WIDTH-1;j++) gotoxy(j,i,"  ");
    }

    gotoxy(MAP_X+(MAP_WIDTH/2)-7,MAP_Y+5,"+--------------------------+");
    gotoxy(MAP_X+(MAP_WIDTH/2)-7,MAP_Y+6,"| TEAM PROJECT : S N A K E |");
    gotoxy(MAP_X+(MAP_WIDTH/2)-7,MAP_Y+7,"+--------------------------+");

    gotoxy(MAP_X+(MAP_WIDTH/2)-7,MAP_Y+9," < PRESS ANY KEY TO START > ");

    gotoxy(MAP_X+(MAP_WIDTH/2)-7,MAP_Y+11,"   �� ��,��,��,�� : Move    ");
    gotoxy(MAP_X+(MAP_WIDTH/2)-7,MAP_Y+12,"   �� P : Pause             ");    
    gotoxy(MAP_X+(MAP_WIDTH/2)-7,MAP_Y+13,"   �� ESC : Quit              ");    

    gotoxy(MAP_X+(MAP_WIDTH/2)-7,MAP_Y+16,"  21800729 �ּ���");
    gotoxy(MAP_X+(MAP_WIDTH/2)-7,MAP_Y+17,"  21800199 ������");   
    
    while(1){
        if(kbhit()){ //Ű�Է¹��� 
            s->key=getch();
            if(s->key==ESC) exit(0); // ESCŰ�� ���� 
            else break; //�ƴϸ� �׳� ��� ���� 
        } 
        gotoxy(MAP_X+(MAP_WIDTH/2)-7,MAP_Y+9," < PRESS ANY KEY TO START > ");
        Sleep(400);
        gotoxy(MAP_X+(MAP_WIDTH/2)-7,MAP_Y+9,"                            ");
        Sleep(400);
        
    }
    reset(s); // ������ �ʱ�ȭ  
}
 
void reset(Game *s){
    int i;
    system("cls"); //ȭ���� ���� 
    draw_map(s); //�� �׵θ��� �׸� 
    while (kbhit()) getch(); //���ۿ� �ִ� Ű���� ���� 
    
    s->dir=LEFT; // ���� �ʱ�ȭ  
    s->speed=100; // �ӵ� �ʱ�ȭ 
    s->length=5; //�� ���� �ʱ�ȭ 
    s->score=0; //���� �ʱ�ȭ 
    for(i=0;i<s->length;i++){ //�� ���밪 �Է� 
        s->x[i]=MAP_WIDTH/2+i;
        s->y[i]=MAP_HEIGHT/2;
        gotoxy(MAP_X+s->x[i],MAP_Y+s->y[i],"S");
    }
    gotoxy(MAP_X+s->x[0],MAP_Y+s->y[0],"O"); //�� �Ӹ� �׸� 
    food(s); // food ����  
}
 
void draw_map(Game *s){ //�� �׵θ� �׸��� �Լ� 
    int i,j;
    for(i=0;i<MAP_WIDTH;i++){
        gotoxy(MAP_X+i,MAP_Y,"��");
    }
    for(i=MAP_Y+1;i<MAP_Y+MAP_HEIGHT-1;i++){
        gotoxy(MAP_X,i,"��");
        gotoxy(MAP_X+MAP_WIDTH-1,i,"��");
    }
    for(i=0;i<MAP_WIDTH;i++){
        gotoxy(MAP_X+i,MAP_Y+MAP_HEIGHT-1,"��");
    }
}
 
void move(Game *s, int dir){
    int i;
 
    if(s->x[0]==s->food_x&&s->y[0]==s->food_y){ //food�� �浹���� ��� 
        s->score+=10; //���� ���� 
        food(s); //���ο� food �߰� 
        s->length++; //�������� 
        s->x[s->length-1]=s->x[s->length-2]; //���θ��� ���뿡 �� �Է� 
        s->y[s->length-1]=s->y[s->length-2];
    }
    if(s->x[0]==0||s->x[0]==MAP_WIDTH-1||s->y[0]==0||s->y[0]==MAP_HEIGHT-1){ //���� �浹���� ��� 
        game_over(s);
        return; //game_over���� ������ �ٽ� �����ϰ� �Ǹ� ���⼭���� �ݺ��ǹǷ� 
                //return�� ����Ͽ� move�� ������ �κ��� ������� �ʵ��� �մϴ�. 
    }
    for(i=1;i<s->length;i++){ //�ڱ���� �浹�ߴ��� �˻� 
        if(s->x[0]==s->x[i]&&s->y[0]==s->y[i]){
            game_over(s);
            return;
        }
    }
    
    gotoxy(MAP_X+s->x[s->length-1],MAP_Y+s->y[s->length-1],"  "); //���� �������� ���� 
    for(i=s->length-1;i>0;i--){ //������ǥ�� ��ĭ�� �ű� 
        s->x[i]=s->x[i-1];
        s->y[i]=s->y[i-1];
    }
    gotoxy(MAP_X+s->x[0],MAP_Y+s->y[0],"S"); //�Ӹ��� �ִ����� �������� ��ħ 
    if(dir==LEFT) --s->x[0]; //���⿡ ���� ���ο� �Ӹ���ǥ(x[0],y[0])���� ���� 
    if(dir==RIGHT) ++s->x[0];
    if(dir==UP) --s->y[0]; 
    if(dir==DOWN) ++s->y[0];     
    gotoxy(MAP_X+s->x[i],MAP_Y+s->y[i],"O"); //���ο� �Ӹ���ǥ���� �Ӹ��� �׸� 
}
 
void pause(Game *s){ // pŰ�� ������ ��� ������ �Ͻ� ���� 
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
 
void game_over(Game *s){ //�������� �Լ� 
    gotoxy(MAP_X+(MAP_WIDTH/2)-6,MAP_Y+5,"+----------------------+");
    gotoxy(MAP_X+(MAP_WIDTH/2)-6,MAP_Y+6,"|      GAME OVER..     |");
    gotoxy(MAP_X+(MAP_WIDTH/2)-6,MAP_Y+7,"+----------------------+");
    gotoxy(MAP_X+(MAP_WIDTH/2)-6,MAP_Y+8," YOUR SCORE : ");
    printf("%d", s->last_score=s->score);
    
    gotoxy(MAP_X+(MAP_WIDTH/2)-7,MAP_Y+12," Press any keys to restart.. ");
    gotoxy(MAP_X+(MAP_WIDTH/2)-7,MAP_Y+14," Press m to open user menu ");
    
    if(s->score>s->best_score) {
        s->best_score=s->score;
    gotoxy(MAP_X+(MAP_WIDTH/2)-4,MAP_Y+10,"�� BEST SCORE ��");
    }
    Sleep(500);
        while (kbhit()) getch();
    s->key=getch();
    title(s);
}
 
void food(Game *s){
    int i;
    
    int food_crush_on=0;//food�� �� ������ǥ�� ���� ��� on 
    int r=0; //���� ������ �絿�Ǵ� ���� 
    gotoxy(MAP_X,MAP_Y+MAP_HEIGHT," YOUR SCORE: "); //����ǥ�� 
    printf("%3d, LAST SCORE: %3d, BEST SCORE: %3d", s->score, s->last_score, s->best_score);
    
    while(1){            
        food_crush_on=0;    
        srand((unsigned)time(NULL)+r); //����ǥ���� 
        s->food_x=(rand()%(MAP_WIDTH-2))+1;    //������ ��ǥ���� ���� 
        s->food_y=(rand()%(MAP_HEIGHT-2))+1;
        
        for(i=0;i<s->length;i++){ //food�� �� ����� ��ġ���� Ȯ��  
            if(s->food_x==s->x[i]&&s->food_y==s->y[i]){
                food_crush_on=1; //��ġ�� food_crush_on �� on 
                r++;
break;
            }
        }
        
        if(food_crush_on==1) continue; //������ ��� while���� �ٽ� ���� 
            
        gotoxy(MAP_X+s->food_x,MAP_Y+s->food_y,"��"); //�Ȱ����� ��� ��ǥ���� food�� ��� 
        s->speed-=3; //�ӵ� ���� 
        break;
        
    }
}

void status(Game *s){ //���� ������ ���� �ִ� �Լ� 
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