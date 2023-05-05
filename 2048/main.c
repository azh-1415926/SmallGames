#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "GameScreen.h"
#include "GameControl.h"
static time_t startTime=0;
static void clearScreen(){
    #if _WIN32
    system("cls");
    #elif __linux__
    system("clear");
    #endif
}
static void showTime(){
    time_t endTime=time(NULL);
    time_t costTime=endTime-startTime;
    printf("Time %ld%ld:%ld%ld  ",costTime/(60*10),costTime/60%10,(costTime%60-costTime%10)/10,costTime%10);
}
static void addRandomPoint(int count){
    int pos=-1;
    for(int i=0;i<count;i++){
        pos=-1;
        while(isInvaild(pos)){
            pos=getRandomNumber(16);
            if(isFull()){
                return;
            }
        }
        addPoint(pos,(getRandomNumber(1)+1)*2);
    }
}
int main(){
    printf("**************\n");
    printf("**2048**\n");
    printf("**************\n");
    printf("              \n");
    printf(" [ 1 ]-- Play --  \n");
    printf(" [ 2 ]-- Exit --  \n");
    int option=-1;
    if(scanf("%d",&option)!=1)
        scanf("%*s");
    switch (option)
    {
        case 1:
        startTime=time(NULL);
        initalGame();
        addRandomPoint(2);
        do{
            clearScreen();
            showTime();
            printf("  Score:%d  Zero:%d\n",getScore(),getZero());
            showGameScreen();
            switch (getUserControl())
            {
            case MOVE_FRONT:
                moveFront();
                if(!isFull()){
                    addRandomPoint(2);
                }
                break;
            case MOVE_LEFT:
                moveLeft();
                if(!isFull()){
                    addRandomPoint(2);
                }
                break;
            case MOVE_RIGHT:
                moveRight();
                if(!isFull()){
                    addRandomPoint(2);
                }
                break;
            case MOVE_BEHIND:
                moveBehind();
                if(!isFull()){
                    addRandomPoint(2);
                }
                break;
            default:
                break;
            }
        }while(isWin()==0);
        clearScreen();
        showTime();
        printf("  Score:%d  Zero:%d\n",getScore(),getZero());
        showGameScreen();
        if(isWin()==-1){
            printf("Game Over,your score is %d.\n",getScore());
        }else{
            printf("You win,your score is %d.\n",getScore());
        }
        case 2:
            break;
        default:
            break;
    }
    return 0;
}