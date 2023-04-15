#ifndef _GAME_MAP_H_
#define _GAME_MAP_H_
#include <stdio.h>
#include <stdbool.h>
void showGameScreen();
void addRandomPoint();
void moveFront();
void moveLeft();
void moveRight();
void moveBehind();
bool isInvaild(int pos);
int isWin(int pos);
#endif /* _GAME_MAP_H_ */
