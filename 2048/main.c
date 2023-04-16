#include <stdio.h>
#include <stdlib.h>
#include "GameScreen.h"
#include "GameControl.h"
static void clearScreen(){
    #if _WIN32
    system("cls");
    #elif __linux__
    system("clear");
    #endif
}
static void addRandomPoint(int count){
    int pos=-1;
    for(int i=0;i<count;i++){
        pos=-1;
        while(isInvaild(pos)){
            pos=getRandomNumber(16);
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
        initalGame();
        addRandomPoint(2);
        while (!isWin())
        {
            clearScreen();
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
        }
        case 2:
            break;
        default:
            break;
    }
    return 0;
}