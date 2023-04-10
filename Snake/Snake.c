#include "Snake.h"
static char _head='Q';
static char _body='O';
static struct snake snakeBody={1,1,1};
static int lastLength=1;
void initalizeSnake(char head,char body){
    _head=head;
    _body=body;
}
void setSnakeHead(int pos){
    snakeBody.head=pos;
    snakeBody.tail=snakeBody.head;
}
char getHead(){
    return _head;
}
char getBody(){
    return _body;
}
void eatFood(){
    snakeBody.length++;
}
int moveSnakeHead(int pos){
    int temp=snakeBody.head;
    if(pos!=-1){
        snakeBody.head=pos;
    }
    return temp;
}
int moveSnakeTail(int pos){
    int temp=snakeBody.tail;
    printf("length:%d,",snakeBody.length);
    if(snakeBody.length==lastLength){
        if(pos!=-1){
            snakeBody.tail=pos;
        }
    }else{
        printf("pos:%d\n",pos);
        temp=-1;
        if(pos!=-1){
            lastLength++;
        }
    }
    printf("lastlength:%d\n",lastLength);
    return temp;
}