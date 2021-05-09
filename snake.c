#include"game.h"


int main(){
    Game s[100];
    title(s);
    
    Users ulist[100];

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
        move(s, s->dir, ulist); 
        
        if(s->status_on==1) status(s); // statusǥ�� 
    }
        
}
    
///////////////////////////MAIN END////////////////////////////////