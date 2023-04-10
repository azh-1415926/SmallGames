#include "GameScreen.h"
#include "Snake.h"
#include "linkQueue.h"
#include "GameControl.h"
#include <stdlib.h>
static linkQueue snakeShape=NULL;
int main(){
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
    initalizeSnake(_head,_body);
    setBoard('*','-','|');
    setSnakeHead(pos);
    addPoint(pos,getHead());
    pos=getAPoint();
    addPoint(pos,_food);
    showGameScreen();
    int i=1;
    while(1){
        pos=moveSnakeHead(-1);
        //test
        if(i==1){
            addPoint(pos-2*(_columns+2),_food);
            addPoint(pos-3*(_columns+2),_food);
            i=0;
        }
        addPoint(pos,getHead());
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
        }else if(ch==_body){
            break;
        }
        pos=moveSnakeHead(pos);
        if(!linkQueueIsEmpty(snakeShape)){
            printf("pos %d set body\n",pos);
            addPoint(pos,getBody());
        }else{
            printf("pos %d set empty\n",pos);
            addPoint(pos,_filler);
        }
        pPos=(int*)malloc(sizeof(int));
        *pPos=pos;
        linkQueueEnqueue(snakeShape,pPos);
            pPos=(int*)linkQueueFront(snakeShape);
            pos=moveSnakeTail(*pPos);
            if(pos!=-1){
                linkQueueDequeue(snakeShape);
                addPoint(*pPos,_body);
                addPoint(pos,_filler);
                printf("The new tail:%d\n",*pPos);
                printf("The old tail:%d\n",pos);
                free(pPos);
            }else{
                pos=moveSnakeTail(-1);
                //addPoint(*pPos,getBody());
                //addPoint(pos,getBody());
            }
    }
    linkQueueFree(&snakeShape);
    return 0;
}