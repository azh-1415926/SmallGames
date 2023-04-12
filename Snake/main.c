#include "GameScreen.h"
#include "Snake.h"
#include "linkQueue.h"
#include "GameControl.h"
#include <stdlib.h>
static linkQueue snakeShape=NULL;
static void clearScreen(){
    #if _WIN32
    system("cls");
    #elif __linux__
    system("clear");
    #endif
}
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
    initalizeSnake(pos);
    setBoard('*','-','|');
    addPoint(getAPoint(),_food);
    showGameScreen();
    while(1){
        pos=getHead();
        addPoint(pos,_head);
        clearScreen();
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
    return 0;
}