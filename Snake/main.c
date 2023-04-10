#include "GameScreen.h"
#include "Snake.h"
#include "linkQueue.h"
#include "GameControl.h"
#include <stdlib.h>
#include <windows.h>
static linkQueue snakeShape=NULL;
int main(){
    char _food='X';
    char _filler=' ';
    int _rows=7;
    int _columns=20;
    int pos=(_rows+2)/2*(_columns+2)+(_columns+2)/2;
    int* pPos=NULL;
    int i=1;
    int currAction=MOVE_FRONT;
    int lastAction=currAction;
    linkQueueInitalize(&snakeShape);
    initalizeGameScreen(_rows,_columns,_filler);
    initalizeGame(_rows,_columns);
    initalizeSnake('Q','O');
    setBoard('*','-','|');
    setSnakeHead(pos);
    addPoint(pos,getHead());
    pos=getAPoint();
    addPoint(pos,_food);
    showGameScreen();
    while(1){
        //get head
        pos=moveSnakeHead(-1);
        if(i==1){
            addPoint(pos-2*(_columns+2),_food);
            addPoint(pos-3*(_columns+2),_food);
        }
        //printf("Head:%d\n",pos);
        //judge invaild
        if(moveIsInvaild(currAction)){
            currAction=lastAction;
        }
        //get move pos
        pos=movePoint(pos,currAction);
        if(pos==-1){
            break;
        }
        //set head pos
        i=addPoint(pos,getHead());
        if(i==-1){
            eatFood();
        }
        //printf("mov head to %d\n",pos);
        //save head and recv last head
        pos=moveSnakeHead(pos);
        if(!linkQueueIsEmpty(snakeShape)){
            //printf("pos %d set body\n",pos);
            addPoint(pos,getBody());
        }else{
            //printf("pos %d set empty\n",pos);
            addPoint(pos,_filler);
        }
        //save new body
        pPos=(int*)malloc(sizeof(int));
        *pPos=pos;
        linkQueueEnqueue(snakeShape,pPos);
        //if(!linkQueueIsEmpty(snakeShape)){
            pPos=(int*)linkQueueFront(snakeShape);
            //printf("The old tail:%d\n",*pPos);
            pos=moveSnakeTail(*pPos);
            //printf("The curr tail:%d\n",pos);
            if(pos!=-1){
                linkQueueDequeue(snakeShape);
                free(pPos);
                //printf("delete tail:%d\n",pos);
                addPoint(pos,_filler);
            }else{
                pos=moveSnakeTail(-1);
                //printf("maintain tail:%d\n",pos);
                addPoint(pos,getBody());
            }
            //printf("The new tail:%d\n",pos);
        //}
        system("cls");
        showGameScreen();
        Sleep(1000);
    }
    linkQueueFree(&snakeShape);
    return 0;
}