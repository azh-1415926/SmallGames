#include "Snake.h"
static struct snake snakeBody={1,1,1};
static int lastLength=1;
void initalizeSnake(int pos){
    snakeBody.head=pos;
    snakeBody.tail=snakeBody.head;
}
int getHead(){
    return snakeBody.head;
}
int getTail(){
    return snakeBody.tail;
}
void eatFood(){
    snakeBody.length++;
}
int moveSnakeHead(int pos){
    int temp=snakeBody.head;
    snakeBody.head=pos;
    return temp;
}
int moveSnakeTail(int pos){
    int temp=snakeBody.tail;
    if(snakeBody.length==lastLength){
        snakeBody.tail=pos;
    }else{
        temp=-1;
        lastLength++;
    }
    return temp;
}