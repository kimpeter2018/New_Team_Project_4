#include"game.h"
#include"user.h"

////////////////////////////MAIN START//////////////////////////////
int main(){
    Game s[100];
    title(s);
    
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
        move(s, s->dir);
        
        if(s->status_on==1) status(s); // status표시   
    }
}
    
///////////////////////////MAIN END////////////////////////////////