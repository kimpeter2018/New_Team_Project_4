# New_Team_Project_4
New Idea! Snake Game!
#### Team Project done by Hyeonmin Kim and Seongchan Choi




## 1. 프로그램 소개
This program is a simlpe snake game with score board feature. <br> <br>
When the game is over the player can choose to add the score to the score board <br>
The name can be 60 characters long <br>
<br>

The main functions of this program are: 
* CRUD function (Create, Read, Update, Delete)
* Search function (search by player's name)
* Save + Load function
  * Can save the updated score board to a text file and can load it when the program starts
  * If there is no text file, then it is created automatically

## 2. 빌드 방식
    제공 되어 있는 Makefile을 통해 간단하게 빌드 할 수 있다.
        make - object file 및 executive 파일 생성
        make clean - 생성 되어있는 object파일과 executive 파일을 제거한다

    Makefile 을 사용하지 않고
        $gcc -c snake.c user.c game.c 을 command라인에서 실행 한 후
        $gcc -o snake snake.o user.o game.o 를 통해서 빌드 할 수도 있다

## 3. 사용법
The controls are typical of Snake Game:
* ⏴⏵⏶⏷ : Move snake,
* P : Pause game,
* ESC : Exit program.
<br><br>
When the game is over, the menu for the scoreboard appears.


## 4. 팀 소개
1. 김현민 21800199
   * 이메일 주소 : 21800199@handong.edu
   * 맡은 역할
     * Main 함수 및 CRUD기능이 있는 user.c user.h 작성
     * GameOver 이후 Menu 실행 구현
     * .gitignore 생성
     * README.md 작성
     * Makefile 작성
2. 최성찬 21800729
   * 이메일 주소 : 21800729@handong.edu
   * 맡은 역할
     * game.c game.h 작성
     * 디자인
     * Wiki 작성
