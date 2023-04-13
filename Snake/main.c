#include "GameScreen.h"
#include "Snake.h"
#include "linkQueue.h"
#include "GameControl.h"
#include <stdlib.h>
#include <time.h>
static linkQueue snakeShape=NULL;
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
int main(){
    printf("**************\n");
    printf("**Snake**\n");
    printf("**************\n");
    printf("              \n");
    printf(" [ 1 ]-- Play --  \n");
    printf(" [ 2 ]-- Exit --  \n");
    int option=-1;
    if(scanf("%d",&option)!=1)
        scanf("%*s");
    if(option==1)
    {
        char _head='Q';
        char _body='O';
        char _food='X';
        char _filler=' ';
        char ch='-';
        int _rows=7;
        int _columns=20;
        int pos=(_rows+2)/2*(_columns+2)+(_columns+2)/2;
        int* pPos=NULL;
        int currAction=MOVE_FRONT;
        int lastAction=currAction;
        linkQueueInitalize(&snakeShape);
        initalizeGameScreen(_rows,_columns,_filler);
        initalizeGame(_rows,_columns);
        initalizeSnake(pos);
        setBoard('*','-','|');
        addPoint(getAPoint(),_food);
        startTime=time(NULL);
        while(1){
            pos=getHead();
            addPoint(pos,_head);
            clearScreen();
            showTime();
            printf("Score %d\n",getLength()*5);
            showGameScreen();
            currAction=getUserControl();
            if(moveIsInvaild(currAction)){
                currAction=lastAction;
            }
            lastAction=currAction;
            pos=movePoint(pos,currAction);
            if(pos==-1){
                break;
            }
            ch=getPointByIndex(pos);
            if(ch==_food){
                eatFood();
                addPoint(getAPoint(),_food);
            }else if(ch==_body){
                break;
            }
            pos=moveSnakeHead(pos);
            if(pos!=getTail()){
                addPoint(pos,_body);
                pPos=(int*)malloc(sizeof(int));
                *pPos=pos;
                linkQueueEnqueue(snakeShape,pPos);
                pPos=(int*)linkQueueFront(snakeShape);
                pos=moveSnakeTail(*pPos);
                if(pos!=-1){
                    addPoint(pos,_filler);
                    linkQueueDequeue(snakeShape);
                    free(pPos);
                }
            }else{
                addPoint(pos,_filler);
                moveSnakeTail(getHead());
            }
        }
        linkQueueFree(&snakeShape);
        printf("Game Over!,the score is %d\n",getLength()*5);
    }else if(option==2){
        printf("Exit!\n");
    }else{
        printf("Fatal error!\n");
    }
    return 0;
}