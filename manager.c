#include "manager.h"

void list(Users *u, int count){
    printf("\nName            score\n");
    printf("-----------------------------------\n");
    for(int i = 0; i < count; i ++){
    if(u[i].score == -1) continue;
    printf("%2d ", i+1);
    readDa(&u[i]);
    }
}

int dataNo(Users *u, int count){
    int no;
    list(u, count);
    printf("번호는 (최소: 0)? ");
    scanf("%d", &no);
    
    return no;
}

int selectMenu(){
    int menu;
    printf("\n*** 즐거운 쇼핑 ***\n");
    printf("1. 조회\n");
    printf("2. 추가\n");
    printf("3. 수정\n");
    printf("4. 삭제\n");
    printf("5. 파일저장\n");
    printf("6. 검색\n");
    printf("0. 종료\n\n");
    printf("=> 원하는 메뉴는? ");
    scanf("%d", &menu);
    printf("****************\n");

    return menu;
}