#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_
#include <stdio.h>
#include <stdbool.h>
void showGameScreen();
void addPoint(int pos,int number);
int getScore();
void moveFront();
void moveLeft();
void moveRight();
void moveBehind();
bool isInvaild(int pos);
bool isFull();
int isWin();
#endif /* _GAME_MAP_H_ */
