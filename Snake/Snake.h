#ifndef _SNAKE_H_
#define _SNAKE_H_
#include <stdio.h>
#include <stdbool.h>
struct snake {
    int head;
    int tail;
    int length;
};
void initalizeSnake(int pos);
int getHead();
int getTail();
void eatFood();
int moveSnakeHead(int pos);
int moveSnakeTail(int pos);
#endif